# Client Web. Comunicaţie cu REST API

## Starting point
Pentru a realiaza această temă, am început de la următoarele surse:
- [Laborator 9] (https://pcom.pages.upb.ro/labs/lab9/lecture.html)

Scheletul pentru client l-am luat de la laboratorul 9, fiind implementate deja funcțiile de a trimite și primi mesaje de la server, care m-au ajutat la implementarea temei.

Am folosit C++.

## Descrierea implementării

Implementarea temei a fost doar a clientului care trimite http request-uri spre server, iar serverul răspunde cu mesaje, care sunt interpretate de client și utilizatorul poate vedea rezultatul în urma rulării comenzilor.

Am creat multiple clase pentru a putea implementa funcționalitățile cerute de temă și pentru a putea face o separare a responsabilităților, aceste clase sunt mai exact:

### Body
Această clasă este folosită pentru a crea un body pentru request, avem field-uri pentru string si field-uri pentru int, care vor fi folosite pentru a crea un body de tip json, mai ușor.

### Header & Cookie
Aceste clase sunt folosite pentru a crea un header și cookie pentru request, avem field-uri pentru string, care vor fi folosite pentru a crea un header de tip json, mai ușor.

### Request
Această clasă este folosită pentru a crea request-ul propriu-zis, avem field-uri pentru path, method, body, header și cookie, care vor fi folosite pentru a crea un request;

### Command
Clasa se ocupă cu parsarea comenzilor și cu alcătuirea request-ului, în funcție de comanda primită de la utilizator, având pentru fiecare comandă o metodă, unde se cere și se validează input-ul de la utilizator, iar apoi se creează request-ul cu ajutorul claselor de mai sus, dacă comanda nu este validă se va returna un string gol.

### Response
Clasa este o utilitară care îmi pune la dispoziție metode ce mă ajută să obțin anumite date din response-ul primit de la server, cum ar fi status code-ul, body-ul, session cookie-ul, token-ul.

Implementarea propriu zisă se află în fișierul `client.cpp`, unde am implementat o buclă infinită, în care se cere input-ul de la utilizator, se validează input-ul și se apelează metoda corespunzătoare comenzii, iar dacă comanda nu este validă se va afișa un mesaj de eroare. În acest while se mai află niște if-uri pentru câteva comenzi, întrucât era nevoie să parsez token-ul, session cokie-ul sau să afișez cărțile într-un anumit mod.

Când primesc un request de la server, afișez status code-ul și respectiv body-ul, dacă este cazul (pentru erorile de la server și pentru afișarea cărților).
Mereu când fac un request deschid un socket, trimit request-ul și primesc răspunsul, iar apoi închid socket-ul și eliberez memoria alocată pentru response;

## Feedback

O temă drăguță, unde a fost nevoie de multă atenție la detalii (validare, parsare corectă)

Provocări ciudate:
 - este nevoie să deschid și să închid socket-ul pentru fiecare request
 - este nevoie de a trimite session cookie-ul pentru a primi acces la bibliotecă (În postman când îl puneam în Authorization, primeam access, dar în programul meu nu funcționa, se pare că în postman se pune automat)

<center><h2>Mulțumesc mult pentru efortul depus.</h2></center>


