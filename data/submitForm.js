const submitButton = document.getElementById("submitButton");
submitButton.addEventListener("click", submitForm);

function submitForm() {
	const xhttp = new XMLHttpRequest();
	xhttp.onload = function() {
		alert("Changes applied!");
	}
	// TODO: the request doesn't seem to be getting sent
	xhttp.open("POST", "/", true);
	xhttp.send("red=0&green=111&blue=95");
}
