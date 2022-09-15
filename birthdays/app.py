import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        #Add the user's entry into the database
        name = request.form.get("name")
        birthday = request.form.get("date")

        if not name or not birthday:
            return render_template("index.html", message="Invalid Name or birthday!!")

        #used datetime module to extract day and date from input
        date = datetime.datetime.strptime(birthday, "%Y-%m-%d")
        day = date.day
        month = date.month

        #insert into database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        return redirect("/")

    else:

        #Display the entries in the database on index.html
        days = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", days=days)


@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")

    db.execute("DELETE FROM birthdays WHERE id = ?", id)

    return redirect("/")


@app.route("/update", methods=["POST"])
def update():
    id = request.form.get("id")
    return render_template("edit.html", id=id)


@app.route("/edit", methods=["POST"])
def edit():

        #Edit the user's entry into the database
        name = request.form.get("name")
        id = request.form.get("id")
        birthday = request.form.get("date")

        if not name or not birthday:
            return render_template("edit.html", message="Invalid Name or birthday!!", id=id)

        #use datetime module to extract day and date from input
        date = datetime.datetime.strptime(birthday, "%Y-%m-%d")
        day = date.day
        month = date.month

        #insert into database
        db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?;", name, month, day, id)
        return redirect("/")