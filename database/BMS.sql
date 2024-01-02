CREATE TABLE Customer (
		CustomerID SERIAL,
		LastName VARCHAR(100) NOT NULL,
		FirstName VARCHAR(100) NOT NULL,
		DateOfBirth DATE NOT NULL,
		EmailID VARCHAR(200) NOT NULL,
		PhoneNumber VARCHAR(20) NOT NULL,
		TaxID VARCHAR(20) NOT NULL UNIQUE,
		CustomerAddress VARCHAR(200) NOT NULL,
		CustomerPassword VARCHAR(100) NOT NULL,
		
		PRIMARY KEY (CustomerID)
);

CREATE TABLE Account (
		AccountID SERIAL,
		CustomerID INT NOT NULL,
		AccountType VARCHAR(20) NOT NULL,
		CurrentBalance DECIMAL(10, 5) NOT NULL,
		DateOpened DATE,
		DateClosed DATE,
		AccountStatus BOOLEAN NOT NULL,
	
		PRIMARY KEY (AccountID),
		FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE Transactions (
		TransactionID SERIAL,
		AccountID INT NOT NULL,
		TransactionDate DATE NOT NULL,
		Amount INT NOT NULL,
	
		PRIMARY KEY (TransactionID),
		FOREIGN KEY (AccountID) REFERENCES Account (AccountID)
)

ALTER SEQUENCE customer_customerid_seq RESTART WITH 100000001;
ALTER SEQUENCE account_accountid_seq RESTART WITH 101;

