--�� ���� ��� ������ ���������� ����� :)
--������� �������

SELECT * INTO [DriverLarge] FROM [Driver]

SELECT * INTO [DriverLargeIndex] FROM [Driver]

SELECT * INTO [CarLarge] FROM [Car]

SELECT * INTO [CarLargeIndex] FROM [Car]

SELECT * INTO [TripLarge] FROM [Trip]

SELECT * INTO [TripLargeIndex] FROM [Trip]

--���������, ������ ���������

INSERT INTO [CarLarge]
SELECT [ID], [Model], [Number], [Capacity], [FuelConsumption]
FROM [Car]

INSERT INTO [CarLargeIndex]
SELECT [ID], [Model], [Number], [Capacity], [FuelConsumption]
FROM [Car]

INSERT INTO [DriverLarge]
SELECT [ID], [FirstName], [LastName], [Category], [TabelID]
FROM [Driver]

INSERT INTO [DriverLargeIndex]
SELECT [ID], [FirstName], [LastName], [Category], [TabelID]
FROM [Driver]

INSERT INTO [TripLarge]
SELECT [DriverID], [CarID], [DepartureTime], [ArrivalTime], [DeparturePoint], [ArrivalPoint], [Distance]
FROM [Trip]

INSERT INTO [TripLargeIndex]
SELECT [DriverID], [CarID], [DepartureTime], [ArrivalTime], [DeparturePoint], [ArrivalPoint], [Distance]
FROM [Trip]

GO 100000


--�������� ������ � ������� �������� ����������

CREATE NONCLUSTERED INDEX IX_ ON [CarLargeIndex]
(
	Model ASC,
	FuelConsumption ASC
)

SET STATISTICS TIME ON
SET STATISTICS IO ON


--������ ���������� ������� � ��� �������

SELECT Model, FuelConsumption
FROM CarLarge
WHERE FuelConsumption > 25

SELECT Model, FuelConsumption
FROM CarLargeIndex
WHERE FuelConsumption > 25

--�������� ��������� ���������:
/*
(2200242 row(s) affected)
Table 'CarLarge'. Scan count 1, logical reads 12660, physical reads 0, read-ahead reads 12288, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.

 SQL Server Execution Times:
   CPU time = 922 ms,  elapsed time = 12847 ms.

(2200242 row(s) affected)
Table 'CarLargeIndex'. Scan count 1, logical reads 8555, physical reads 0, read-ahead reads 12, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.

 SQL Server Execution Times:
   CPU time = 781 ms,  elapsed time = 12808 ms.
*/

--�������� ������������� �������� �� ���������� ������. ������� �������� �������

CREATE NONCLUSTERED INDEX IDX_ ON [DriverLargeIndex]
(
	FirstName ASC,
	Category ASC
)

CREATE NONCLUSTERED INDEX IDX2_ ON [TripLargeIndex]
(
	DriverID ASC,
	ArrivalPoint ASC
)


--������ �������� ��������� �������

SELECT FirstName, Category
FROM [DriverLarge] INNER JOIN [TripLarge] ON ID = DriverID
WHERE ArrivalPoint = 'Singapore'

SELECT FirstName, Category
FROM [DriverLargeIndex] INNER JOIN [TripLargeIndex] ON ID = DriverID
WHERE ArrivalPoint = 'Singapore'

--� ���������, ���-�� ����� �� ���, Microsoft SQL Management Studio ����� ��������� ������ � �����:
--An error occurred while executing batch. Error message is: ������ ���������� ���� "System.OutOfMemoryException".
--��������, ������ ������� �����, ������� ������ ����������������� �� ������� ������� (1�� �����)

SELECT TOP (1000000) FirstName, Category
FROM [DriverLarge] INNER JOIN [TripLarge] ON ID = DriverID
WHERE ArrivalPoint = 'Singapore'

SELECT TOP (1000000) FirstName, Category
FROM [DriverLargeIndex] INNER JOIN [TripLargeIndex] ON ID = DriverID
WHERE ArrivalPoint = 'Singapore'


--�������� ��������� ���������:
/*
(1000000 row(s) affected)
Table 'Workfile'. Scan count 0, logical reads 0, physical reads 0, read-ahead reads 0, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.
Table 'Worktable'. Scan count 0, logical reads 0, physical reads 0, read-ahead reads 0, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.
Table 'DriverLarge'. Scan count 1, logical reads 1, physical reads 0, read-ahead reads 0, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.
Table 'TripLarge'. Scan count 1, logical reads 21055, physical reads 0, read-ahead reads 0, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.

 SQL Server Execution Times:
   CPU time = 1047 ms,  elapsed time = 8464 ms.

(1000000 row(s) affected)
Table 'TripLargeIndex'. Scan count 147, logical reads 4487, physical reads 0, read-ahead reads 0, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.
Table 'DriverLargeIndex'. Scan count 1, logical reads 1, physical reads 0, read-ahead reads 0, lob logical reads 0, lob physical reads 0, lob read-ahead reads 0.

 SQL Server Execution Times:
   CPU time = 766 ms,  elapsed time = 8089 ms.
*/

--��� �����, � ����� ������� ������������������ ������� ��������� ������ ����� ������� ������� (��� ����� ������ �� ������ �� ������� ������, �� � �� ����� "logical reads")