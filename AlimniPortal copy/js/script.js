// Smooth Scrolling for internal links
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        document.querySelector(this.getAttribute('href')).scrollIntoView({
            behavior: 'smooth'
        });
    });
});

// Form Validation
const form = document.querySelector('form');
form.addEventListener('submit', (e) => {
    const name = document.querySelector('input[name="name"]');
    const email = document.querySelector('input[name="_replyto"]');
    const message = document.querySelector('textarea[name="message"]');

    if (!name.value || !email.value || !message.value) {
        alert("Please fill all fields before submitting.");
        e.preventDefault();  // Prevent form submission
    } else {
        alert("Thank you for your message!");
    }
});

// Sample Streak System (for engagement purposes)
const streaks = JSON.parse(localStorage.getItem('streaks')) || 0;
document.getElementById('streak').innerText = `Current Streak: ${streaks} days`;

document.getElementById('engage-btn').addEventListener('click', () => {
    let newStreaks = streaks + 1;
    localStorage.setItem('streaks', newStreaks);
    document.getElementById('streak').innerText = `Current Streak: ${newStreaks} days`;
});

// Add dynamic events listing (this could come from an API)
const eventsList = [
    { name: "Alumni Meet 2024", date: "15th March 2024" },
    { name: "IIIT Pune Hackathon", date: "10th April 2024" },
    { name: "Annual Fundraising Gala", date: "25th May 2024" },
];

const eventsSection = document.getElementById('events-list');
eventsList.forEach(event => {
    const eventItem = document.createElement('li');
    eventItem.className = 'list-group-item';
    eventItem.textContent = `${event.name} - Date: ${event.date}`;
    eventsSection.appendChild(eventItem);
});
