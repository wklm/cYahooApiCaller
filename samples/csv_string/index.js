var express = require('express');
var app = express();

app.get('/', function (req, res) {
  res.send('Hello World!');

var exec = require('child_process').exec,
    child;

child = exec('./csv_string',
  function (error, stdout, stderr) {
    console.log('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
      console.log('exec error: ' + error);
    }
});
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});
