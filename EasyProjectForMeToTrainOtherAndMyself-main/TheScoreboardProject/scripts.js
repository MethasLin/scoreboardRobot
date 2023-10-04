const scoreElements = [];

// Initialize the array with score elements
for (let i = 1; i <= 17; i++) {
    scoreElements.push(document.getElementById(`score_${i}`));
}

// Function to submit a score
function submitScore(inputName) {
    // Find the index of the element in the array based on the input name
    const index = parseInt(inputName.split('_')[1]) - 1;

    // Get the value entered in the input field
    const inputElement = scoreElements[index].querySelector('input');
    const score = parseInt(inputElement.value);

    // Update the scores array with the new score
    scores[index] = score;

    // Sort the scores array in descending order
    scores.sort((a, b) => b - a);

    // Update the display order based on the sorted scores
    for (let i = 0; i < scores.length; i++) {
        scoreElements[i].querySelector('input').value = scores[i];
    }
}

// Initial scores for each team (change these as needed)
const scores = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];