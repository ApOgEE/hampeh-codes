SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `kamyarblog`
--
CREATE DATABASE `kamyarblog` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `kamyarblog`;

-- --------------------------------------------------------

--
-- Table structure for table `myentries`
--

CREATE TABLE IF NOT EXISTS `myentries` (
  `id` int(11) NOT NULL auto_increment,
  `title` varchar(128) NOT NULL,
  `body` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `myentries`
--

INSERT INTO `myentries` (`id`, `title`, `body`) VALUES
(2, 'my first post', 'this is the first post'),
(3, 'this is the second post', 'hi there... the second blog post');
