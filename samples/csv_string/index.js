var express = require('express');


var bodyParser = require('body-parser');

var app = express();

app.use(bodyParser());


app.get('/', function(req, res){

  var html = '<form action="/" method="post">' +
               '<input type="text" name="company" placeholder="compnay" />' +
               '<br>' +
               '<input type="text" name="beginday" placeholder="beginday" />' +
               '<br>' +
               '<input type="text" name="begimonth" placeholder="beginmonth" />' +
               '<br>' +
               '<input type="text" name="beginyear" placeholder=".beginyear.." />' +
               '<br>' +
               '<input type="text" name="endday" placeholder=".endday.." />' +
               '<br>' +
               '<input type="text" name="endmonth" placeholder=".endmonth.." />' +
               '<br>' +
               '<input type="text" name="endyear" placeholder=".endyear.." />' +
               '<br>' +
               '<input type="text" name="endyear" placeholder=".strike.." />' +
               '<br>' +
               '<button type="submit">Submit</button>' +
            '</form>';
               
  res.send(html);
});


app.post('/', function(req, res){
  var company = req.body.company;
  var beginday = req.body.beginday;
  var beginmonth = req.body.beginmonth;
  var beginyear = req.body.beginyear;
  var endday = req.body.endday;
  var endmonth = req.body.endmonth;
  var endyear = req.body.endyear;
  var strike = req.body.strike;
  
  var html = 'company: ' + company + '.<br>' + 
            'beginday: ' + beginday + '.<br>';

             
  res.send(html);
});

app.listen(3000);