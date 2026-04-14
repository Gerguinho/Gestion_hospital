-- Lister les patients
SELECT * FROM Patient;

-- Patients par service
SELECT s.nom_service, COUNT(p.id_patient)
FROM Service s
JOIN Patient p ON s.id_service = p.id_service
GROUP BY s.nom_service;

-- Vérification intégrité
SELECT * FROM Consultation WHERE id_patient IS NULL;
