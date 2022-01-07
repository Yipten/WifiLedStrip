const redInput = document.getElementById("redInput");
const redInputValue = document.getElementById("redInputValue");
redInput.addEventListener("input", updateRedInputValue);
function updateRedInputValue() {
	redInputValue.innerHTML = redInput.value;
}

const greenInput = document.getElementById("greenInput");
const greenInputValue = document.getElementById("greenInputValue");
greenInput.addEventListener("input", updateGreenInputValue);
function updateGreenInputValue() {
	greenInputValue.innerHTML = greenInput.value;
}

const blueInput = document.getElementById("blueInput");
const blueInputValue = document.getElementById("blueInputValue");
blueInput.addEventListener("input", updateBlueInputValue);
function updateBlueInputValue() {
	blueInputValue.innerHTML = blueInput.value;
}

// display initial value when page loads
updateRedInputValue();
updateGreenInputValue();
updateBlueInputValue();

