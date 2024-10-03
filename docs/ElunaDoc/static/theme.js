const themeToggle = document.getElementById('themeToggle');

// Check if user preference exists in local storage
const currentTheme = localStorage.getItem('theme');
if (currentTheme) {
    document.documentElement.classList.add(currentTheme);
}

themeToggle.addEventListener('click', () => {
    document.documentElement.classList.toggle('dark-mode');

    // Store user preference in local storage
    if (document.documentElement.classList.contains('dark-mode')) {
        localStorage.setItem('theme', 'dark-mode');
    } else {
        localStorage.setItem('theme', '');
    }
    
    hljs.highlightAll();
});

hljs.highlightAll();