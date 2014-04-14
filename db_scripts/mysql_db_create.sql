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

# Asteroid 2
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID) 
VALUES (6, 10.8e2, 0, 4.2e7, -1.7e3, 0, -0.00015, 1e6, "AsteriodBody");

# Asteroid 1
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID) 
VALUES (5, 10.8e2, -4.2e7, 0, 0, -1.7e3, -0.00015, 1e6, "AsteriodBody");

# Top Gas Giant
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID, primaryMaskRed, primaryMaskBlue, primaryMaskGreen, secondaryMaskRed, secondaryMaskBlue, secondaryMaskGreen, tertiaryMaskRed, tertiaryMaskBlue, tertiaryMaskGreen) 
VALUES (4, 5.9721986e22, 0, 3e9, 0, 0, -0.00015, 4e7, "GasPlanet", 170, 0, 0, 170, 85, 255, 170, 255, 255);

# Bottom Gas Giant
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID, primaryMaskRed, primaryMaskBlue, primaryMaskGreen, secondaryMaskRed, secondaryMaskBlue, secondaryMaskGreen, tertiaryMaskRed, tertiaryMaskBlue, tertiaryMaskGreen) 
VALUES (3, 5.9721986e22, 0, -3e9, 0, 0, -0.00015, 4e7, "GasPlanet", 134, 230, 72, 38, 177, 48, 32, 249, 94);

# Second Moon
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID) 
VALUES (2, 7.3459e22, -3.8e8, 0, 0, -1023, -0.00015, 3.4e6, "RingworldPlanet");

#Moon
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID) 
VALUES (1, 7.3459e22, 3.8e8, 0, 0, 1023, -0.00015, 3.4e6, "Moon");

#Earth
INSERT INTO body (id, mass, positionx, positiony, velocityx, velocityy, rotationRate, diameter, resourceID, primaryMaskRed, primaryMaskBlue, primaryMaskGreen, secondaryMaskRed, secondaryMaskBlue, secondaryMaskGreen, tertiaryMaskRed, tertiaryMaskBlue, tertiaryMaskGreen) 
VALUES (0, 5.9721986e24, 0, 0, 0, 0, 0.0001, 1.27e7, "WaterPlanet", 124, 119, 198, 148, 212, 166, 0, 0, 0);

CREATE USER 'pixspace'@'%' IDENTIFIED BY 'pixspace';
GRANT SELECT, INSERT, UPDATE, DELETE on pixspace.body TO 'pixspace'@'%';
