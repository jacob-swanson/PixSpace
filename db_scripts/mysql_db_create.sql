CREATE DATABASE pixspace;
USE pixspace;

CREATE TABLE body
(
id INT NOT NULL,
mass DOUBLE NOT NULL,
positionx DOUBLE NOT NULL,
positiony DOUBLE NOT NULL,
velocityx DOUBLE NOT NULL,
velocityy DOUBLE NOT NULL,
rotationRate DOUBLE NOT NULL,
diameter DOUBLE NOT NULL,
resourceID VARCHAR(50) NOT NULL,
primaryMaskRed INT,
primaryMaskBlue INT,
primaryMaskGreen INT,
secondaryMaskRed INT,
secondaryMaskBlue INT,
secondaryMaskGreen INT,
tertiaryMaskRed INT,
tertiaryMaskBlue INT,
tertiaryMaskGreen INT,
PRIMARY KEY (id)
) Engine InnoDB;

CREATE USER 'pixspace'@'%' IDENTIFIED BY 'pixspace';
GRANT SELECT, INSERT, UPDATE, DELETE on pixspace.body TO 'pixspace'@'%';

#Moon
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID) VALUES (1, 7.3459e22, 3.8e8, 0, 0, 1023, -0.00015, 3.4e6, "Moon");
#Earth
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID, primaryMaskRed, primaryMaskBlue, primaryMaskGreen, secondaryMaskRed, secondaryMaskBlue, secondaryMaskGreen, tertiaryMaskRed, tertiaryMaskBlue, tertiaryMaskGreen) VALUES (0, 5.9721986e24, 0, 0, 0, 0, 0.0001, 1.27e7, "WaterPlanet", 124, 119, 198, 148, 212, 166, 0, 0, 0);

