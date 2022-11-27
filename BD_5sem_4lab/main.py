import psycopg2
from psycopg2 import sql

conn = psycopg2.connect(
    database='lab1',
    user='posgres',
    password='admin',
    host='localhost',
    port='5432'
)
