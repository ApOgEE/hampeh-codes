<html>
<head>
<title><?=$blogtitle?></title>
</head>
<body>
<?=form_open('blog/login') ?>
	Username: <input type="text" name="username" id="username" value="" /><br />
	Password: <input type="password" name="password" id="password" value="" /><br />
	<input type="submit" value="Login" />
<?=form_close() ?>
</body>
</html>
