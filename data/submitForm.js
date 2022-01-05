// add event listeners & get array of input element names
const mainForm = document.getElementById("mainForm");
const inputElements = mainForm.elements;
const inputNames = [];
for (let i = 0; i < inputElements.length; i++) {
	inputElements[i].addEventListener("change", submitForm);
	inputNames[i] = inputElements[i].name;
}

// sends a POST request containing user input using AJAX
function submitForm() {
	const xhttp = new XMLHttpRequest();
	xhttp.open("POST", "/submit", true);
	xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	dataStr = getFormData();
	xhttp.send(dataStr);
}

// generates string of user input for POST request
function getFormData() {
	dataStr = "";
	inputNames.forEach(function(value, index, array) {
		if (value) {
			dataStr += value + "=" + inputElements[value].value + "&";
		}
	});
	// remove the last ampersand
	dataStr = dataStr.slice(0, -1);
	return dataStr;
}
