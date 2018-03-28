-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server versie:                10.1.16-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win32
-- HeidiSQL Versie:              9.5.0.5196
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Databasestructuur van monc wordt geschreven
CREATE DATABASE IF NOT EXISTS `monc` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `monc`;

-- Structuur van  tabel monc.accounts wordt geschreven
CREATE TABLE IF NOT EXISTS `accounts` (
  `ID` int(11) NOT NULL,
  `Rekeningnummer` varchar(10) NOT NULL,
  `Saldo` int(11) NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `Rekeningnummer` (`Rekeningnummer`),
  CONSTRAINT `accounts_ibfk_1` FOREIGN KEY (`Rekeningnummer`) REFERENCES `debitcard` (`Rekeningnummer`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumpen data van tabel monc.accounts: ~1 rows (ongeveer)
/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
INSERT INTO `accounts` (`ID`, `Rekeningnummer`, `Saldo`) VALUES
	(7899, 'RA45PE2', 56084);
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;

-- Structuur van  tabel monc.debitcard wordt geschreven
CREATE TABLE IF NOT EXISTS `debitcard` (
  `Rekeningnummer` varchar(10) NOT NULL,
  `Pincode` int(4) NOT NULL,
  `Pasnummer` varchar(11) NOT NULL,
  `Kansen` int(2) NOT NULL,
  PRIMARY KEY (`Rekeningnummer`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumpen data van tabel monc.debitcard: ~1 rows (ongeveer)
/*!40000 ALTER TABLE `debitcard` DISABLE KEYS */;
INSERT INTO `debitcard` (`Rekeningnummer`, `Pincode`, `Pasnummer`, `Kansen`) VALUES
	('RA45PE2', 1234, 'D188BAB', 0);
/*!40000 ALTER TABLE `debitcard` ENABLE KEYS */;

-- Structuur van  tabel monc.klanten wordt geschreven
CREATE TABLE IF NOT EXISTS `klanten` (
  `ID` int(11) NOT NULL,
  `Achternaam` varchar(50) NOT NULL,
  `Voornaam` varchar(50) NOT NULL,
  `Geboortedatum` date NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumpen data van tabel monc.klanten: ~0 rows (ongeveer)
/*!40000 ALTER TABLE `klanten` DISABLE KEYS */;
INSERT INTO `klanten` (`ID`, `Achternaam`, `Voornaam`, `Geboortedatum`) VALUES
	(7899, 'Jansen', 'Piet', '1978-02-12');
/*!40000 ALTER TABLE `klanten` ENABLE KEYS */;

-- Structuur van  tabel monc.transacties wordt geschreven
CREATE TABLE IF NOT EXISTS `transacties` (
  `TransactieID` int(11) NOT NULL,
  `Rekeningnummer` varchar(10) NOT NULL,
  `HoeveelGeld` float NOT NULL,
  `Beschrijving` varchar(100) DEFAULT NULL,
  `Datum` date NOT NULL,
  PRIMARY KEY (`TransactieID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumpen data van tabel monc.transacties: ~0 rows (ongeveer)
/*!40000 ALTER TABLE `transacties` DISABLE KEYS */;
INSERT INTO `transacties` (`TransactieID`, `Rekeningnummer`, `HoeveelGeld`, `Beschrijving`, `Datum`) VALUES
	(562015, 'RA45PE2', 30, NULL, '2016-07-30');
/*!40000 ALTER TABLE `transacties` ENABLE KEYS */;

-- Structuur van  tabel monc.werknemers wordt geschreven
CREATE TABLE IF NOT EXISTS `werknemers` (
  `ID` int(11) NOT NULL,
  `Achternaam` varchar(50) NOT NULL,
  `Voornaam` varchar(50) NOT NULL,
  `Geboortedatum` date NOT NULL,
  `Functie` varchar(20) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumpen data van tabel monc.werknemers: ~0 rows (ongeveer)
/*!40000 ALTER TABLE `werknemers` DISABLE KEYS */;
INSERT INTO `werknemers` (`ID`, `Achternaam`, `Voornaam`, `Geboortedatum`, `Functie`) VALUES
	(3552, 'Tian', 'Sebas', '1989-01-31', 'Helpdeskmedewerker');
/*!40000 ALTER TABLE `werknemers` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
