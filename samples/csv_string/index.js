var express = require('express');


var bodyParser = require('body-parser');

var app = express();

app.use(bodyParser());


app.get('/', function(req, res){


               
 res.sendfile('layout.html');
});


app.post('/', function(req, res){
  var company = req.body.cname;
  var beginday = req.body.bday;
  var beginmonth = req.body.bmonth;
  var beginyear = req.body.byear;
  var endday = req.body.eday;
  var endmonth = req.body.emonth;
  var endyear = req.body.eyear;
  var strike = req.body.strike;
  
  var exec = require('child_process').exec,
    child;

child = exec('./csv_string ' + company + ' ' + beginday + ' ' + beginmonth + ' ' + beginyear + ' ' + endday + ' ' + endmonth + ' ' + endyear + ' ' + strike,
  function (error, stdout, stderr) {
    res.send('stdout: ' + stdout);
    console.log('stderr: ' + stderr);
    if (error !== null) {
      console.log('exec error: ' + error);
    }
});

             
 
});

app.listen(3000);