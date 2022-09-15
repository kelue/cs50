document.querySelector('#contactForm').addEventListener('submit', (e)=>{
    const name = document.querySelector('#name').value;

    window.alert(`${name}, Thank you for your email.`);
    
    // e.preventDefault();
});