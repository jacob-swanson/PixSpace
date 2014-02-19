CREATE DATABASE pixspace;
USE pixspace;

CREATE TABLE sprite
(
spriteId VARCHAR(100) NOT NULL,
sprite VARCHAR(300000) NOT NULL,
PRIMARY KEY (spriteId)
) Engine InnoDB;

CREATE TABLE body
(
id CHAR(44) NOT NULL,
spriteId VARCHAR(100) NOT NULL,
PRIMARY KEY (id),
FOREIGN KEY (spriteId)
REFERENCES sprite(spriteId)
ON DELETE CASCADE
ON UPDATE CASCADE
) Engine InnoDB;

CREATE USER 'pixspace'@'localhost' IDENTIFIED BY 'pixspace';
GRANT SELECT, INSERT, UPDATE, DELETE on pixspace.* TO 'pixspace'@'localhost';
