-- MySQL dump 10.13  Distrib 5.1.60, for redhat-linux-gnu (i386)
--
-- Host: localhost    Database: students_info
-- ------------------------------------------------------
-- Server version	5.1.60

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `students_info`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `students_info` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `students_info`;

--
-- Table structure for table `change_code`
--

DROP TABLE IF EXISTS `change_code`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `change_code` (
  `code` varchar(255) NOT NULL,
  `description` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `change_code`
--

LOCK TABLES `change_code` WRITE;
/*!40000 ALTER TABLE `change_code` DISABLE KEYS */;
INSERT INTO `change_code` VALUES ('0','è½¬ç³»'),('1','ä¼‘å­¦'),('2','å¤å­¦'),('3','é€€å­¦'),('4','æ¯•ä¸š');
/*!40000 ALTER TABLE `change_code` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `changes`
--

DROP TABLE IF EXISTS `changes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `changes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `studentid` int(11) DEFAULT NULL,
  `changes` varchar(255) DEFAULT NULL,
  `rec_time` date DEFAULT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  KEY `studentid` (`studentid`),
  KEY `changes` (`changes`)
) ENGINE=MyISAM AUTO_INCREMENT=52 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `changes`
--

LOCK TABLES `changes` WRITE;
/*!40000 ALTER TABLE `changes` DISABLE KEYS */;
/*!40000 ALTER TABLE `changes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `class`
--

DROP TABLE IF EXISTS `class`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `class` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `monitor` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `monitor` (`monitor`)
) ENGINE=MyISAM AUTO_INCREMENT=32 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `class`
--

LOCK TABLES `class` WRITE;
/*!40000 ALTER TABLE `class` DISABLE KEYS */;
INSERT INTO `class` VALUES (24,'è®¡ç®—æœºäºŒç­','1000'),(25,'è®¡ç®—æœºä¸‰ç­','1000'),(26,'è®¡ç®—æœºå››ç­','1000'),(23,'è®¡ç®—æœºä¸€ç­','2000'),(27,'ç½‘ç»œä¸€ç­',''),(28,'ç½‘ç»œäºŒç­',''),(29,'ç½‘ç»œä¸‰ç­',''),(30,'ä¿¡æ¯ä¸€ç­','');
/*!40000 ALTER TABLE `class` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `department`
--

DROP TABLE IF EXISTS `department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `department` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=MyISAM AUTO_INCREMENT=23 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `department`
--

LOCK TABLES `department` WRITE;
/*!40000 ALTER TABLE `department` DISABLE KEYS */;
INSERT INTO `department` VALUES (21,'æœºç”µå­¦é™¢'),(20,'ä¿¡æ¯å­¦é™¢'),(19,'è®¡ç®—æœºå­¦é™¢'),(22,'åŒ–å­¦åŒ–å·¥å­¦é™¢');
/*!40000 ALTER TABLE `department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `login_users`
--

DROP TABLE IF EXISTS `login_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `login_users` (
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `admin` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`username`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `login_users`
--

LOCK TABLES `login_users` WRITE;
/*!40000 ALTER TABLE `login_users` DISABLE KEYS */;
INSERT INTO `login_users` VALUES ('admin','cc6879ff2b0d1fe6dec8269c9d77aa86',1),('user','c12e01f2a13ff5587e1e9e4aedb8242d',0);
/*!40000 ALTER TABLE `login_users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `punish_levels`
--

DROP TABLE IF EXISTS `punish_levels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `punish_levels` (
  `code` varchar(255) DEFAULT NULL,
  `description` text
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `punish_levels`
--

LOCK TABLES `punish_levels` WRITE;
/*!40000 ALTER TABLE `punish_levels` DISABLE KEYS */;
INSERT INTO `punish_levels` VALUES ('0','è­¦å‘Š'),('1','ä¸¥é‡è­¦å‘Š'),('2','è®°è¿‡'),('3','è®°å¤§è¿‡'),('4','å¼€é™¤');
/*!40000 ALTER TABLE `punish_levels` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `punishment`
--

DROP TABLE IF EXISTS `punishment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `punishment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `studentid` int(11) DEFAULT NULL,
  `levels` varchar(255) DEFAULT NULL,
  `rec_time` date DEFAULT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  KEY `studentid` (`studentid`),
  KEY `levels` (`levels`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `punishment`
--

LOCK TABLES `punishment` WRITE;
/*!40000 ALTER TABLE `punishment` DISABLE KEYS */;
/*!40000 ALTER TABLE `punishment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reward`
--

DROP TABLE IF EXISTS `reward`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reward` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `studentid` int(11) DEFAULT NULL,
  `levels` varchar(255) DEFAULT NULL,
  `rec_time` date DEFAULT NULL,
  `description` text,
  PRIMARY KEY (`id`),
  KEY `studentid` (`studentid`),
  KEY `levels` (`levels`)
) ENGINE=MyISAM AUTO_INCREMENT=23 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reward`
--

LOCK TABLES `reward` WRITE;
/*!40000 ALTER TABLE `reward` DISABLE KEYS */;
/*!40000 ALTER TABLE `reward` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reward_levels`
--

DROP TABLE IF EXISTS `reward_levels`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reward_levels` (
  `code` varchar(255) NOT NULL,
  `description` text,
  PRIMARY KEY (`code`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reward_levels`
--

LOCK TABLES `reward_levels` WRITE;
/*!40000 ALTER TABLE `reward_levels` DISABLE KEYS */;
INSERT INTO `reward_levels` VALUES ('0','æ ¡ç‰¹ç­‰å¥–å­¦é‡‘'),('1','æ ¡ä¸€ç­‰å¥–å­¦é‡‘'),('2','æ ¡äºŒç­‰å¥–å­¦é‡‘'),('3','æ ¡ä¸‰ç­‰å¥–å­¦é‡‘'),('4','ç³»ä¸€ç­‰å¥–å­¦é‡‘'),('5','ç³»äºŒç­‰å¥–å­¦é‡‘'),('6','ç³»ä¸‰ç­‰å¥–å­¦é‡‘');
/*!40000 ALTER TABLE `reward_levels` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `student`
--

DROP TABLE IF EXISTS `student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `student` (
  `id` varchar(255) NOT NULL DEFAULT '',
  `name` varchar(255) NOT NULL,
  `sex` varchar(10) NOT NULL,
  `class` int(11) DEFAULT NULL,
  `department` int(11) DEFAULT NULL,
  `birthday` date DEFAULT NULL,
  `native_place` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `class` (`class`),
  KEY `department` (`department`)
) ENGINE=MyISAM AUTO_INCREMENT=1005020229 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `student`
--

LOCK TABLES `student` WRITE;
/*!40000 ALTER TABLE `student` DISABLE KEYS */;
INSERT INTO `student` VALUES ('3','','ç”·',24,21,NULL,NULL),('2','','ç”·',24,21,NULL,NULL),('ddd','ddd','å¥³',29,20,'1000-01-01','dddd'),('sdfsd','sdfsdf','ç”·',24,21,NULL,NULL),('1005020218','','ç”·',26,21,NULL,NULL),('1','','ç”·',24,21,NULL,NULL),('4','','ç”·',24,21,NULL,NULL),('12','sdf','ç”·',24,21,'2012-12-30','asdf'),('564','','å¥³',23,19,'2012-03-10',NULL),('112323','sfdsdf','å¥³',26,19,'2010-10-10','sdfds');
/*!40000 ALTER TABLE `student` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2013-01-02 14:27:28
