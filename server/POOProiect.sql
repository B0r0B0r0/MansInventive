
IF OBJECT_ID('Utilizatori','u') is not null
	DROP TABLE Utilizatori
GO
create table Utilizatori(
id INT PRIMARY KEY IDENTITY (1,1),
username nvarchar(50),
password nvarchar(255),
email nvarchar(255),
statusAdmin INT
);


IF OBJECT_ID('Dispozitive','u') is not null
	DROP TABLE Dispozitive
GO
create table Dispozitive(
id INT PRIMARY KEY IDENTITY (1,1),
denumire nvarchar(50),
locatie nvarchar(50),
parametru1 INT,
parametru2 INT,
status INT
);

IF OBJECT_ID('UtilizatoriDispozitive','u') is not null
	DROP TABLE UtilizatoriDispozitive
GO
create table UtilizatoriDispozitive(
id INT PRIMARY KEY IDENTITY (1,1),
id_Utilizator INT REFERENCES Utilizatori(id) ON DELETE CASCADE,
id_Dispozitive INT REFERENCES Dispozitive(id) ON DELETE CASCADE
);



IF OBJECT_ID('Register_User') IS NOT NULL 
	DROP PROC Register_User; 
GO
CREATE PROC Register_User 
@user nvarchar(50), 
@parola nvarchar(255),
@email nvarchar(255),
@statusAdmin INT
AS
BEGIN
INSERT INTO Utilizatori(username, password, email, statusAdmin) VALUES (@user,@parola,@email,@statusAdmin);
END 
GO


IF OBJECT_ID('Modify_Password') IS NOT NULL 
	DROP PROC Modify_Password; 
GO
CREATE PROC Modify_Password 
@user nvarchar(50),
@parola nvarchar(255)
AS
BEGIN
UPDATE Utilizatori
SET password=@parola
WHERE username = @user
END 
GO


IF OBJECT_ID('Modify_Email') IS NOT NULL 
	DROP PROC Modify_Email; 
GO
CREATE PROC Modify_Email 
@user nvarchar(50),
@email nvarchar(255)
AS
BEGIN
UPDATE Utilizatori
SET email=@email
WHERE username = @user
END 
GO


IF OBJECT_ID('Register_Dispozitiv') IS NOT NULL 
	DROP PROC Register_Dispozitiv; 
GO
CREATE PROC Register_Dispozitiv 
@user nvarchar(50), 
@denumire nvarchar(255),
@locatie nvarchar(255),
@parametru1 nvarchar(255),
@parametru2 nvarchar(255)
AS
BEGIN
IF EXISTS(SELECT 1 FROM Dispozitive WHERE denumire = @denumire AND locatie = @locatie)
BEGIN
    RAISERROR('Device already exists', 16, 1);
    RETURN;
END

INSERT INTO Dispozitive(denumire, locatie, status, parametru1,parametru2) VALUES (@denumire,@locatie,0,@parametru1,@parametru2);
INSERT INTO UtilizatoriDispozitive(id_Dispozitive,id_Utilizator) VALUES
(
(SELECT MAX(id) from Dispozitive),
(SELECT id from Utilizatori where username=@user)
)
END 
GO


IF OBJECT_ID('Delete_User') IS NOT NULL 
	DROP PROC Delete_User; 
GO
CREATE PROCEDURE Delete_User
    @userId INT
AS
BEGIN
    -- Sterge dispozitivele asociate doar utilizatorului specificat
    DELETE FROM Dispozitive
    WHERE id IN (
        SELECT id_Dispozitive
        FROM UtilizatoriDispozitive
        WHERE id_Utilizator = @userId
        AND NOT EXISTS (
            SELECT 1
            FROM UtilizatoriDispozitive ud2
            WHERE ud2.id_Dispozitive = UtilizatoriDispozitive.id_Dispozitive
            AND ud2.id_Utilizator <> @userId
        )
    );

    -- Sterge inregistrarile asociate utilizatorului din tabela UtilizatoriDispozitive
    DELETE FROM UtilizatoriDispozitive
    WHERE id_Utilizator = @userId;

    -- Sterge utilizatorul
    DELETE FROM Utilizatori
    WHERE id = @userId;
END
GO

IF OBJECT_ID('Get_Dispozitive') IS NOT NULL 
	DROP PROC Get_Dispozitive; 
GO
CREATE PROCEDURE Get_Dispozitive
    @user nvarchar(50)
AS
BEGIN
select u.id ,u.username ,d.denumire, d.locatie, d.parametru1, d.parametru2, d.status from Dispozitive d
inner join UtilizatoriDispozitive ud on ud.id_Dispozitive = d.id
inner join Utilizatori u on u.id=ud.id_Utilizator
where u.username = @user
END
GO


SELECT * FROM Dispozitive
inner join UtilizatoriDispozitive on UtilizatoriDispozitive.id_Dispozitive = Dispozitive.id
inner join Utilizatori on Utilizatori.id = UtilizatoriDispozitive.id_Utilizator
Where Utilizatori.id = 4

IF OBJECT_ID('Delete_Dispozitiv') IS NOT NULL 
	DROP PROC Delete_Dispozitiv; 
GO
CREATE PROCEDURE Delete_Dispozitiv
    @denumire nvarchar(255),
	@locatie nvarchar(255)
AS
BEGIN
	delete from UtilizatoriDispozitive where
	id_Dispozitive = (select id from Dispozitive where denumire = @denumire and locatie = @locatie)

	delete from Dispozitive where denumire = @denumire and locatie = @locatie
	

END
GO


IF OBJECT_ID('Modifica_Status') IS NOT NULL 
	DROP PROC Modifica_Status; 
GO
CREATE PROCEDURE Modifica_Status
    @denumire nvarchar(255),
	@locatie nvarchar(255),
	@status INT
AS select * from Dispozitive
BEGIN
	UPDATE Dispozitive
	SET status=@status
	WHERE denumire=@denumire and locatie=@locatie
	

END
GO

select * from Dispozitive

IF OBJECT_ID('Modify_Dispozitiv') IS NOT NULL 
	DROP PROC Modify_Dispozitiv; 
GO
CREATE PROCEDURE Modify_Dispozitiv
    @denumire nvarchar(255),
	@locatie nvarchar(255),
	@param1 nvarchar(255),
	@param2 nvarchar(255)
AS
BEGIN
	UPDATE Dispozitive
	SET parametru1 =@param1, parametru2 = @param2
	WHERE denumire = @denumire and locatie = @locatie
END
GO

modify_dispozitiv 'termostat', 'camera1', '14', '14'
IF OBJECT_ID('Adauga_Asociere') IS NOT NULL 
	DROP PROC Adauga_Asociere; 
GO
CREATE PROCEDURE Adauga_Asociere
	@user nvarchar(50),
    @denumire nvarchar(255),
	@locatie nvarchar(255)
	
AS
BEGIN
	insert into UtilizatoriDispozitive (id_Dispozitive,id_Utilizator)	values
	(
	(select id from Dispozitive where denumire = @denumire and locatie = @locatie),
	(select id from Utilizatori where username =@user)
	)
END
GO


IF OBJECT_ID('Scoatere_Asociere') IS NOT NULL 
	DROP PROC Scoatere_Asociere; 
GO
CREATE PROCEDURE Scoatere_Asociere
	@user nvarchar(50),
    @denumire nvarchar(255),
	@locatie nvarchar(255)
	
AS
BEGIN
	delete from UtilizatoriDispozitive
	where
	id_Dispozitive = (select id from Dispozitive where denumire = @denumire and locatie = @locatie) and
	id_Utilizator = (select id from Utilizatori where username =@user)
	
END
GO
select * from Dispozitive

exec Modify_Dispozitiv'Bec', 'Baie', '14', '14'

exec Delete_Dispozitiv 'Camera', 'Living'


exec Get_Dispozitive 'user4'

exec Adauga_Asociere 'user5', 'Bec', 'Baie'
exec Scoatere_Asociere 'user3', 'Bec', 'Baie'

select * from Dispozitive where denumire = 'bec' and locatie = 'living'

select * from Utilizatori
select * from Dispozitive
select * from UtilizatoriDispozitive

delete from Utilizatori
delete from UtilizatoriDispozitive
delete from Dispozitive

drop table UtilizatoriDispozitive
drop table Utilizatori
drop table Dispozitive

exec Register_Dispozitiv 'user1', 'Bec', 'Living', 0,0
exec Register_Dispozitiv 'user2', 'Termostat', 'Living', 0,0
exec Register_Dispozitiv 'user3', 'Camera', 'Living', 0,0
exec Register_Dispozitiv 'user4', 'Bec', 'Baie', 0,0
exec Register_Dispozitiv 'user5', 'Termostat', 'Baie', 0,0

select U.username,D.denumire,D.locatie from Utilizatori U
INNER JOIN UtilizatoriDispozitive UD on U.id=UD.id_Utilizator
INNER JOIN Dispozitive D on D.id = UD.id_Dispozitive



INSERT INTO UtilizatoriDispozitive(id_Dispozitive,id_Utilizator) values (1,2)

EXEC Modify_Password 'user', 'parola'
EXEC Modify_Email 'user', 'gmail'

	

exec Register_User 'user1', 'parola','gmail',0
exec Register_User 'user2', 'parola','gmail',0
exec Register_User 'user3', 'parola','gmail',0
exec Register_User 'user4', 'parola','gmail',0
exec Register_User 'user5', 'parola','gmail',0

select* from Utilizatori
select * from Dispozitive
select * from dispozitiveutilizatori
Select * from Utilizatori where username = 'user3' and password = 'parola'

	exec delete_user 8