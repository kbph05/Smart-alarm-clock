// Gets the current time of the server. Used for testing 

const express = require('express');
app = express();

const date = new Date().toLocaleString('en-US', {
    timeZone : 'America/Vancouver',
});

console.log(date);

app.listen(3000, function () {
    console.log("Express started on port 3000");
});

