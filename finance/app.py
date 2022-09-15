import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = session["user_id"]

    # grab user info from database
    rows = db.execute("SELECT symbol, shares FROM stocksOwned WHERE user_id = ?", user)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user)
    cash = cash[0]["cash"]

    # initialize variables
    stocks = []
    total = cash

    # lookup current stock price values and append values to stocks list
    for row in rows:
        item = lookup(row["symbol"])

        name = item["name"]
        price = item["price"]
        symbol = row["symbol"]
        share = row["shares"]
        amount = price * share
        total += amount

        stocks.append({
            "name": name,
            "price": price,
            "symbol": symbol,
            "share": share,
            "total": amount
        })

    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user = session["user_id"]

    rows = db.execute("SELECT * FROM transactions WHERE user_id = ?", user)

    return render_template("history.html", stocks=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        ticker = request.form.get("symbol")

        if not ticker:
            return apology("Must insert stock ticker")

        result = lookup(ticker.upper())

        if result != None:
            return render_template("quoted.html", stock=result)
        else:
            return apology("stock not found")

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # extract all details from form
        user = request.form.get("username")
        password = request.form.get("password")
        passConfirm = request.form.get("confirmation")

        # check for valid user name
        if not user:
            return apology("Username cannot be blank")
        # check for valid password
        elif not password:
            return apology("Must enter password")
        # check for confirm password input
        elif not passConfirm:
            return apology("Retype password ")
        # check that both password inputs match
        elif password != passConfirm:
            return apology("passwords do not match")

        rows = db.execute("SELECT username FROM users")

        names = []

        for row in rows:
            names.append(row["username"])

        if user in names:
            return apology("username already exists")

        # hash password
        passhash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)

        id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", user, passhash)

        # Remember which user has registered and log them in
        session["user_id"] = id

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # get stock ticker
        symbol = request.form.get("symbol")
        symbol = symbol.upper()

        # get number of shares
        shares = request.form.get("shares")

        # checks for empty inputs and other incorrect inputs
        if not symbol or not shares:
            return apology("Enter a symbol and share amount")

        try:
            if int(shares) < 1:
                return apology("invalid shares")
        except (ValueError, TypeError):
            return apology("invalid shares")

        shares = int(shares)
        # lookup stock info
        stock = lookup(symbol)
        if stock == None:
            return apology("unable to find stock info")
        else:
            price = stock["price"]

        # recall user id
        user = session["user_id"]

        # check user balance
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user)
        cash = rows[0]["cash"]

        # calculate total amount to be spent on purchase
        total = price * shares

        if total > cash:
            return apology("insufficient balance")

        name = stock["name"]

        #add purchase record
        db.execute("INSERT INTO transactions (user_id, stock, symbol, shares, price, type, total) VALUES (?, ?, ?, ?, ?, ?, ?)",
                    user, name, symbol, shares, price, "BUY", total)

        # update user stock holdings
        db.execute("INSERT INTO stocksOwned (user_id, symbol, shares) VALUES (?, ?, ?)", user, symbol, shares)

        cash -= total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user)

        return render_template("buy.html", stock=stock, shares=shares, total=total, cash=cash)

    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user = session["user_id"]
    rows = db.execute("SELECT symbol, shares FROM stocksOwned WHERE user_id = ?", user)

    if request.method == "POST":

        # grab symbols of stocks owned by users
        stocksOwned = []
        for row in rows:
            stocksOwned.append(row["symbol"])

        # initialize data from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # check that input is not blank and user owns the stock
        if not shares:
            return apology("Enter a valid share amount")
        elif not symbol or symbol not in stocksOwned:
            return apology("You don't have this stock")

         # handle negative, fractional and non-numeric input
        try:
            if int(shares) < 1:
                return apology("invalid shares")
        except (ValueError, TypeError):
            return apology("invalid shares")

        # grab the index of the stock in db and check that user is not trying to sell more than he has
        idx = stocksOwned.index(symbol)
        shares = int(shares)

        if shares > rows[idx]["shares"]:
            return apology("Insufficient stocks owned")

        stocksold = lookup(symbol)

        saleprice = stocksold["price"]
        total = shares * saleprice
        name = stocksold["name"]

        #add sale record
        db.execute("INSERT INTO transactions (user_id, stock, symbol, shares, price, type, total) VALUES (?, ?, ?, ?, ?, ?, ?)",
                    user, name, symbol, shares, saleprice, "SELL", total)

        # add total amount sold to cash value
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user)
        cash = cash[0]["cash"] + total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user)

        return render_template("sell.html", shares=shares, name=name, price=saleprice, stocks=rows, total=total, cash=cash)

    if len(rows) == 0:
        render_template("sell.html")
    return render_template("sell.html", stocks=rows)


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():

    if request.method == "POST":
        user = session["user_id"]

        amount = request.form.get("cash")

        if not amount or int(amount) < 1:
            return apology("Enter a valid amount")

        amount = int(amount)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", user)
        cash = cash[0]["cash"] + amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user)

        return render_template("cash.html", amount=amount, cash=cash)

    return render_template("cash.html")