javier.zavala@deinsi.com
Admin010
https://rc.webmail.pair.com/

ssh-keygen -t rsa -C "javier.zavala@deinsi.com"

sed -i 's/lemonade/credere/g' *
migrate -path ./migrations -database postgres://postgres:789@localhost:5433/borrar?sslmode=disable up




cd cdr
go run ./cmd/api/main.go

añadi (./testing) ejemplos de las request para ref, p ej:

en paralelo, voy preparando propuesta
de migracion postgress 

 
(creo que con este avance se cubren las 
    vistas de la maqueta .. )

continuo enfocado en estudiar arqu. 
de lemonade para inspiracion en credere.    
---------------------
1.
(sumulando link que recibe cliente/usuario potencial)
curl "http://localhost:8080/user-info?token=valid-token"

2.
endpoint POST para recepcionar la seleccion
curl -i -v -X POST http://localhost:8080/user-selection \
  -H "Content-Type: application/json" \
  -d '{
    "monto": "3900",
    "selection": "vacaciones",
    "plazo": "3 Meses",
    "periodicidad": "quincenal"
  }'

3.
endpoint POST para registro (ultima vista)
curl -i -v -X POST http://localhost:8080/create-account \
  -H "Content-Type: application/json" \
  -d '{
    "id": "francisco.marquez@gmail.com",
    "password": "123456"
  }'


curl -v http://localhost:3001/get_user_info_by_token -H "Authorization: Bearer $1"



git@github.com:DEINSI-DEVELOP/lemonade_service_go.git
git remote add origin git@github.com:DEINSI-DEVELOP/credere_service.git



mkdir docker
mkdir -p ./cmd/api
cd cmd/api
cp /home/toto/DEINSI/boilerplates/main.go .
cd ../..
cp /home/toto/DEINSI/lemonade_service_go/.gitignore .
mkdir internal
cd internal
mkdir users
cd users
mkdir data
mkdir domain
mkdir presentation
cd ../..


go mod init github.com/DEINSI-DEVELOP/credere_service
go mod init github.com/javierzavalaponce/cdr
export DB_URL="postgres://user:password@localhost:5433/lemonade_db?sslmode=disable"


migrate -path ./migrations -database "$DB_URL" up
migrate -path ./migrations -database "$DB_URL" version
alias mg='migrate -path ./migrations -database "$DB_URL"'
mg up
mg version
mg up
mg down 1


curl -i -X POST $BASE_LEMON/signup   -H "Content-Type: application/json"   -d '{
    "email": "user01.name@mail.com",
    "password": "123",
    "name": "John",
    "last_name_paternal": "Perez",
    "last_name_maternal": "Lopez",
    "phone": "5512345678",
    "accepts_advertising": true,
    "company": "MOTIONFLUID S.A. de C.V.",
    "otp_code": "123456"
  }'
HTTP/1.1 201 Created
Date: Wed, 28 Jan 2026 12:51:09 GMT
Content-Length: 0

export DB_URL="postgres://user:password@localhost:5432/lemonade_db?sslmode=disable"
cd ~/DEINSI/lemonade_service_go/internal/core/data/services/database_service
$migrate -path ./migrations -database "$DB_URL" up

--------------------------------------------------

conecta a puerto 5432 de local a 5432

----------------------------------------------------

-------------------
+ info:
------------------------


curl -X GET "http://13.56.252.230:8066/games/mi-progol/parameters"   -H "Session_id: 70290000100"   -H "Store_id: 1"   -H "Foreign_pos_id: 3"   -H "State_id: 01"   -H "Sequence_number: 2"   -H "Chain_id: 02"   -H "Application_revision: 1"   -H "Accept: text/plain, application/json, application/*+json, */*" 


alias tunelloteria="ssh -i wingo-dev-2024.pem -L 8000:10.1.0.150:80 admin@13.56.252.230"

localhost:8000 apunte al servidor interno 10.1.0.150:80 pasando por 13.56.252.230.




EchoApi
discord  - tiospencer
W+27*XpV}9vDRG2


arquitectura hexagonal
guardamos datos 


rsync -avh /media/toto/38CF-9DE2/bkp_doctorado/doctorado /home/toto

-----------------------------------------------------    

aa5422fd-2109-49d5-a234-a4078d9b3e90

estos son ejemplos de como introducir datos a la database usando 
cliente sql desde consola.


postgres=# INSERT INTO test_backend.users (email, password)
postgres-# VALUES ('javi2@example.com', 'otro HASH_DE_PASSWORD');

Contesta: INSERT 0 1
----------------------------------------------
postgres=# INSERT INTO test_backend.tasks (
    name,
    description,
    user_id
)
postgres-# VALUES (ter
    'otra tarea de prueba',
    'asentar las ideas',
    'aa5422fd-2109-49d5-a234-a4078d9b3e90'
);

'aa5422fd-2109-49d5-a234-a4078d9b3e90'



export DB_URL="postgres://USER:PASSWORD@localhost:5432/TEST_BACKEND_DB?sslmode=disable"



------------------------
$cat 000004_create_tasks_table.down.sql 000004_create_tasks_table.up.sql

DROP TABLE IF EXISTS test_backend.tareas CASCADE;


CREATE TABLE IF NOT EXISTS test_backend.tareas (
    id UUID PRIMARY KEY DEFAULT uuid_generate_v4(),
    titulo VARCHAR(255) NOT NULL,
    descripcion TEXT,
    completada BOOLEAN DEFAULT false,
    usuario_id UUID NOT NULL REFERENCES test_backend.users(id) ON DELETE CASCADE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP
);

-- Índice para consultas por usuario
CREATE INDEX IF NOT EXISTS idx_tareas_usuario_id ON test_backend.tareas(usuario_id);

-- Índice para consultas por estado
CREATE INDEX IF NOT EXISTS idx_tareas_completada ON test_backend.tareas(completada);
------------------------------
no vel el efecto tras correr mi programa,
   en otras palabras , el visor de la extension
   en code no me muestra la tabla nueva.

   Que me esta faltando hacer para visualizar ambas (user y tasks) ?
   como verificar que una migracion se aplica? / se  loggea?

   GRacias ma
   n
---------------------------------


en donde le indico al 


"localhost",
"5432",
"USER",
"PASSWORD",
"TEST_BACKEND_DB",


"disable",
"src/core/data/services/database_service/database_service_postgres/migrations",



dentro de correrparser env

feat: add signin usecase to users feature

asdfasdfasdfasdf
asdfasdfasdfasdfsadf









terminal android
una vez conectada
simular transaccion
instanciamiento



javier.zavala@deinsi.com
Admin010
https://rc.webmail.pair.com/



2.
el el use case falta la funcionalidad 
(pero eso lo indicas en el comentario, asi que espero a cuando lo tengas listo :smile:)

y falta agregar los metodos del servicio y del repositorio (espero a que lo tengas listo :smile:)

cuando hagas un pull request, los cambios deben ser lo minimo posible para que haya una funcionalidad, manda u pr por flujo, por ejemplo no mandes uno con los dos  gets de las tasks, manda un pr para un create, luego otro para un get, etc (es dificil revisar un pr cuando tiene mucho código)

los archivos deben llamarse igual que la struct principal, por ejemplo este CreateTasksUseCase

los nombres metodos de los repositorios deben conicidir con CRUD:
Create, Read, ReadAll, ReadBy, Update, Delete

este modelo tiene:
package tasks_modelstype Task struct {
	ID        int    `json:"id"`
	Title     string `json:"title"`
	Completed bool   `json:"completed"`
}

---------------------------------------------------------------------------


crear tablsa
crear docker yml
imagen postgress 17
correr contenedor con pgrs17
SQL tools
data queda en settings
git log --graph --oneline --all --decorate
