?php
$getLastRelay = file_get_contents('relay.json');
$getRelay = (array) json_decode($getLastRelay, true);
?><!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Document</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.0/css/bootstrap.min.css">
    <style type="text/css">
        body {
          background-color:#eee;
          text-align:center;
          padding:85px 0;
        }
    .toggle {
          position:relative;
          display:inline-block;
          width:100px;
          height:160px;
          background-color:#bbb;
          -webkit-border-radius:4px;
          -moz-border-radius:4px;
          border-radius:4px;
          text-align:center;
        }
    .toggle input {
          width:100%;
          height:100%;
          margin:0 0;
          padding:0 0;
          position:absolute;
          top:0;
          right:0;
          bottom:0;left:0;
          z-index:2;
          cursor:pointer;
          opacity:0;
          filter:alpha(opacity=0);
        }
    .toggle label {
          display:block;
          position:absolute;
          top:1px;
          right:1px;
          bottom:1px;
          left:1px;
          background-image:-webkit-linear-gradient(top,#fff 0%,#ddd 50%,#fff 50%,#eee 100%);
          background-image:-moz-linear-gradient(top,#fff 0%,#ddd 50%,#fff 50%,#eee 100%);
          background-image:-ms-linear-gradient(top,#fff 0%,#ddd 50%,#fff 50%,#eee 100%);
          background-image:-o-linear-gradient(top,#fff 0%,#ddd 50%,#fff 50%,#eee 100%);
          background-image:linear-gradient(top,#fff 0%,#ddd 50%,#fff 50%,#eee 100%);
          -webkit-box-shadow:0 2px 3px rgba(0,0,0,0.4),
            inset 0 -1px 1px #888,
            inset 0 -5px 1px #bbb,
            inset 0 -6px 0 white;
          -moz-box-shadow:0 2px 3px rgba(0,0,0,0.4),
            inset 0 -1px 1px #888,
            inset 0 -5px 1px #bbb,
            inset 0 -6px 0 white;
          box-shadow:0 2px 3px rgba(0,0,0,0.4),
            inset 0 -1px 1px #888,
            inset 0 -5px 1px #bbb,
            inset 0 -6px 0 white;
          -webkit-border-radius:3px;
          -moz-border-radius:3px;
          border-radius:3px;
          font:normal 30px Arial,Sans-Serif;
          color:#666;
          text-shadow:0 1px 0 white;
          cursor:text;
        }

    .toggle label:before {
          content:attr(data-off);
          position:absolute;
          top:20px;
          right:0;
          left:0;
          z-index:4;
        }

    .toggle label:after {
          content:attr(data-on);
          position:absolute;
          right:0;
          bottom:20px;
          left:0;
          color:#666;
          text-shadow:0 -1px 0 #eee;
        }

    .toggle input:checked + label {
          background-image:-webkit-linear-gradient(top,#eee 0%,#ccc 50%,#fff 50%,#eee 100%);
          background-image:-moz-linear-gradient(top,#eee 0%,#ccc 50%,#fff 50%,#eee 100%);
          background-image:-ms-linear-gradient(top,#eee 0%,#ccc 50%,#fff 50%,#eee 100%);
          background-image:-o-linear-gradient(top,#eee 0%,#ccc 50%,#fff 50%,#eee 100%);
          background-image:linear-gradient(top,#eee 0%,#ccc 50%,#fff 50%,#eee 100%);
          -webkit-box-shadow:0 0 1px rgba(0,0,0,0.4),
            inset 0 1px 7px -1px #ccc,
            inset 0 5px 1px #fafafa,
            inset 0 6px 0 white;

    .toggle input:checked + label:before {
          z-index:1;
          top:26px;
        }

    .toggle input:checked + label:after {
          bottom:14px;
          color:#aaa;
          text-shadow:none;
          z-index:4;
        }
    </style>
</head>
<body>

    <form action="process.php" method="post">
        <div class="container">
            <div class="row justify-content-md-center">
                <div class="col col-lg-2">
                    <h3 class="<?php echo ($getRelay['relay1'] ? 'text-primary' : 'text-danger'); ?>">Relay 1</h3>
                    <span class="toggle">
                        <input type="checkbox" name="relay1" <?php echo ($getRelay['relay1'] ? 'checked' : ''); ?>>
                        <label data-off="&#10006;" data-on="&#10004;"></label>
                    </span>
                </div>
                <div class="col col-lg-2">
                    <h3 class="<?php echo ($getRelay['relay2'] ? 'text-primary' : 'text-danger'); ?>">Relay 2</h3>
                    <span class="toggle">
                        <input type="checkbox" name="relay2" <?php echo ($getRelay['relay2'] ? 'checked' : ''); ?>>
                        <label data-off="&#10006;" data-on="&#10004;"></label>
                    </span>
                </div>
          </div>
    </form>
    <script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
    <script type="text/javascript">
        $(function(){
            $('input[type=checkbox]').change(function(){
                $('form').submit();
            });
        });
    </script>
</body>
</html>
