<html>
<head>
<title><?=$blogtitle?></title>
</head>
<body>
<h1><?=$pagehead?></h1>

<p>
Hi<?=" ".$username?>, welcome to the experimental blog
</p>

<?php foreach($query->result() as $row): ?>
<h3><?=$row->title?></h3>
<p><?=$row->body?></p>
<hr/>
<?php endforeach; ?>
<?=$logout?>
</body>
</html>
