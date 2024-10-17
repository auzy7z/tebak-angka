CREATE DATABASE game;

USE game;

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
);

CREATE TABLE redeem_codes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    code VARCHAR(50) NOT NULL UNIQUE
);

INSERT INTO redeem_codes (code) VALUES ('IgnJgfsig885'), ('Hggsytr881h'), ('Aq0962nvks9');
