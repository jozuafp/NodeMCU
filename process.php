<?php
$relay1 = isset($_POST['relay1']) && $_POST['relay1'] ? true : false;
$relay2 = isset($_POST['relay2']) && $_POST['relay2'] ? true : false;

$json = [
    'relay1' => $relay1 ? 1 : 0,
    'relay2' => $relay2 ? 1 : 0,
];

file_put_contents('relay.json', json_encode($json));

@header("Location: http://echo.web.id/relay/");
