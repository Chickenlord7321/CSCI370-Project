-- Every user's password is 123 because A) I'm lazy and don't want to remember different passwords, and B) there's no constraint saying passwords have to be unique.

INSERT INTO Users VALUES (
'000000',
'admin',
'123',
TO_DATE('2025-04-10', 'YYYY-MM-DD')
);

INSERT INTO Users VALUES (
'000001',
'caleb',
'123',
TO_DATE('2025-04-11', 'YYYY-MM-DD')
);

INSERT INTO Users VALUES (
'000002',
'huizhu',
'123',
CURRENT_DATE
);

INSERT INTO Users VALUES (
'000003',
'Number1MovieFanboy',
'123',
CURRENT_DATE
);
