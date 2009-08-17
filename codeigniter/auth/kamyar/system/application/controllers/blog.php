<?php

class Blog extends Controller {

	function Blog()
	{
		parent::Controller();	
		//$this->load->library('database');
		$this->load->library('session');
		$this->load->helper('url');
		$this->load->helper('form');
		$this->load->scaffolding('myentries');
	}
	
	function index()
	{
		if ($this->checksession()) {
			$data['blogtitle'] = 'Kamyar Blog';
			$data['pagehead'] = 'Kamyar Blog';
			$data['query'] = $this->db->get('myentries');
			$data['logout'] = anchor('blog/logout','logout');
			$data['username'] = $this->session->userdata('username');
			$this->load->view('blog_view',$data);
		}
	}
	
	function checksession()
	{
		//$this->session->userdata('session_id');
		if ($this->session->userdata('user_id')) {
			return TRUE;
		}	else {
			$this->login();
			return FALSE;
		}
	}
	
	function login()
	{
		$username = $this->input->post('username', true);
		$password = $this->input->post('password', true);
		if($username || $password)
		{
		  if($this->try_login(array('username' => $username, 'password' => $password))) {
				redirect('blog');
			}
		}
		
		//echo "please login";
		$data['blogtitle'] = 'Kamyar Blog';
		//$data['pagehead'] = 'Kamyar Blog';

		echo $password; 
		$this->load->view('login_view',$data);
		
		//$this->load->view('login_view');
	}
	
	function try_login($condition = array())
	{
		//echo $condition['password'];
		if ($condition['password'] == 'kambing') {
			$logindata = array('username' => 'ApOgEE', 'user_id' => 'hahah');
			$this->session->set_userdata($logindata);
			return TRUE;
		} else {
			return FALSE;
		}
	}
	
	function logout() {
		$this->session->unset_userdata('user_id');
		redirect('blog');
	}
	
	function register() {
		

	}
}

/* End of file welcome.php */
/* Location: ./system/application/controllers/welcome.php */
