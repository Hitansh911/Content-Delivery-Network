// Initial Cache Data
let cache = ['', 'Video1', 'Image1', '', ''];

// Content Queue
let contentQueue = [];

// Update the Cache Table on the webpage
function updateCacheTable() {
    const cacheTable = document.getElementById('cacheTable');
    cacheTable.innerHTML = ''; // Clear current table

    // Populate with current cache
    cache.forEach((content, index) => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${index}</td>
            <td>${content || 'Empty'}</td>
        `;
        cacheTable.appendChild(row);
    });
}

// Enqueue content (add content ID to the queue)
function enqueueContent() {
    const contentIDInput = document.getElementById('contentID');
    const contentID = parseInt(contentIDInput.value);

    if (!contentID && contentID !== 0) {
        alert('Please enter a valid content ID');
        return;
    }

    // Enqueue operation (add content ID to the queue)
    contentQueue.push(contentID);
    contentIDInput.value = ''; // Clear the input

    // Display content in the queue
    const queueList = document.getElementById('contentQueueList');
    const li = document.createElement('li');
    li.textContent = `Content ID: ${contentID}`;
    queueList.appendChild(li);

    // Process content (dequeue and cache it)
    processContent();
}

// Dequeue and process content (check cache or fetch)
function processContent() {
    if (contentQueue.length === 0) {
        return; // No content in the queue
    }

    const contentID = contentQueue.shift(); // Dequeue content ID
    const index = contentID % 5; // Hash function to map to cache index

    // Check if content is already in cache (non-empty check)
    if (cache[index] !== '') {
        showPopup(`Content found in cache: ${cache[index]}`);
    } else {
        alert(`Content not found in cache. Fetching content with ID: ${contentID}`);
        cache[index] = `Content_${contentID}`; // Simulate fetching and caching
    }

    updateCacheTable(); // Update the cache table on the UI
}

// Show popup message centered on the screen
function showPopup(message) {
    const popup = document.createElement('div');
    popup.classList.add('popup');
    popup.textContent = message;

    // Create a close button for the popup
    const closeButton = document.createElement('button');
    closeButton.textContent = 'Close';
    closeButton.onclick = () => popup.remove();

    popup.appendChild(closeButton);
    document.body.appendChild(popup);
}

// Call the updateCacheTable function on page load to show the initial cache state
window.onload = updateCacheTable;
