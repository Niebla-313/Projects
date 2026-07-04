\c proyecto_bi;
-- =================================================================================
-- 1. CREACION DE USUARIO Y ROL (Siempre al principio)
-- =================================================================================
DROP USER IF EXISTS user_prueba;
CREATE USER user_prueba WITH PASSWORD '1234';

DROP ROLE IF EXISTS readwrite;
CREATE ROLE readwrite;

-- Asignar el rol al usuario de una vez
GRANT readwrite TO user_prueba;

-- Permiso dinámico de conexión a la Base de Datos actual
DO $$
DECLARE
    current_db TEXT;
BEGIN
    SELECT current_database() INTO current_db;
    EXECUTE 'GRANT CONNECT ON DATABASE ' || quote_ident(current_db) || ' TO readwrite';
END $$;

-- =================================================================================
-- 2. PERMISOS GLOBALES Y POR DEFECTO (Para asegurar lo que ya existe y lo del futuro)
-- =================================================================================
-- NOTA: Usamos minúsculas para asegurar coincidencia exacta con el estándar de Postgres
GRANT USAGE, CREATE ON SCHEMA seguro_g26473471, seguro_dw_g26473471 TO readwrite;
GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA seguro_g26473471, seguro_dw_g26473471 TO readwrite;
GRANT USAGE, SELECT, UPDATE ON ALL SEQUENCES IN SCHEMA seguro_g26473471, seguro_dw_g26473471 TO readwrite;

--Cualquier secuencia nueva que se cree en el futuro HEREDA los permisos
ALTER DEFAULT PRIVILEGES IN SCHEMA seguro_dw_g26473471 GRANT USAGE, SELECT, UPDATE ON SEQUENCES TO readwrite;
ALTER DEFAULT PRIVILEGES IN SCHEMA seguro_g26473471 GRANT USAGE, SELECT, UPDATE ON SEQUENCES TO readwrite;

-- =================================================================================
-- 3. CREACION DE LA SECUENCIA Y ALTERACION DE LA TABLA
-- =================================================================================

-- =================================================================================
-- CONFIGURACIÓN PARA DIM_TIEMPO
-- =================================================================================

-- 1. Creamos la secuencia oficial para la tabla de tiempo
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_tiempo_sk_seq START WITH 1;

-- 2. Le asignamos la secuencia como valor por defecto a SK_DIM_TIEMPO
ALTER TABLE seguro_dw_g26473471.dim_tiempo 
ALTER COLUMN sk_dim_tiempo SET DEFAULT nextval('seguro_dw_g26473471.dim_tiempo_sk_seq');

-- 3. Sincronizamos el contador por si el archivo 01 ya insertó registros fijos
SELECT setval('seguro_dw_g26473471.dim_tiempo_sk_seq', COALESCE(MAX(sk_dim_tiempo), 1)) FROM seguro_dw_g26473471.dim_tiempo;

-- 4. Otorgamos los permisos de uso al rol readwrite
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_tiempo_sk_seq TO readwrite;

-- =================================================================================
-- SECUENCIA PARA LA TABLA DIM_PRODUCTO
-- =================================================================================
-- Ahora que las reglas por defecto existen, la secuencia nacerá con permisos para 'readwrite'
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_producto_sk_seq START WITH 1;

ALTER TABLE seguro_dw_g26473471.dim_producto 
ALTER COLUMN sk_dim_producto SET DEFAULT nextval('seguro_dw_g26473471.dim_producto_sk_seq');

-- Sincronizar por si el archivo anterior insertó datos fijos
SELECT setval('seguro_dw_g26473471.dim_producto_sk_seq', COALESCE(MAX(sk_dim_producto), 1)) FROM seguro_dw_g26473471.dim_producto;

-- Permiso explícito de emergencia a la secuencia por si acaso
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_producto_sk_seq TO readwrite;


-- =================================================================================
-- CONFIGURACIÓN PARA DIM_CLIENTE
-- =================================================================================

-- 1. Creamos la secuencia oficial para la tabla de clientes
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_cliente_sk_seq START WITH 1;

-- 2. Le asignamos la secuencia como valor por defecto a SK_DIM_CLIENTE
ALTER TABLE seguro_dw_g26473471.dim_cliente 
ALTER COLUMN sk_dim_cliente SET DEFAULT nextval('seguro_dw_g26473471.dim_cliente_sk_seq');

-- 3. Sincronizamos el contador por si ya existen registros cargados
SELECT setval('seguro_dw_g26473471.dim_cliente_sk_seq', COALESCE(MAX(sk_dim_cliente), 1)) FROM seguro_dw_g26473471.dim_cliente;

-- 4. Otorgamos los permisos de uso al rol readwrite
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_cliente_sk_seq TO readwrite;


-- =================================================================================
-- CONFIGURACIÓN PARA DIM_EVALUACION_SERVICIO
-- =================================================================================

-- 1. Creamos la secuencia oficial para la tabla de evaluación de servicio
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_evaluacion_servicio_sk_seq START WITH 1;

-- 2. Le asignamos la secuencia como valor por defecto a SK_DIM_EVALUACION_SERVICIO
ALTER TABLE seguro_dw_g26473471.dim_evaluacion_servicio 
ALTER COLUMN sk_dim_evaluacion_servicio SET DEFAULT nextval('seguro_dw_g26473471.dim_evaluacion_servicio_sk_seq');

-- 3. Sincronizamos el contador por si ya existen registros cargados
SELECT setval('seguro_dw_g26473471.dim_evaluacion_servicio_sk_seq', COALESCE(MAX(sk_dim_evaluacion_servicio), 1)) FROM seguro_dw_g26473471.dim_evaluacion_servicio;

-- 4. Otorgamos los permisos de uso al rol readwrite
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_evaluacion_servicio_sk_seq TO readwrite;


-- =================================================================================
-- CONFIGURACIÓN PARA DIM_CONTRATO
-- =================================================================================

-- 1. Creamos la secuencia oficial para la tabla de contratos
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_contrato_sk_seq START WITH 1;

-- 2. Le asignamos la secuencia como valor por defecto a SK_DIM_CONTRATO
ALTER TABLE seguro_dw_g26473471.dim_contrato 
ALTER COLUMN sk_dim_contrato SET DEFAULT nextval('seguro_dw_g26473471.dim_contrato_sk_seq');

-- 3. Sincronizamos el contador por si ya existen registros cargados
SELECT setval('seguro_dw_g26473471.dim_contrato_sk_seq', COALESCE(MAX(sk_dim_contrato), 1)) FROM seguro_dw_g26473471.dim_contrato;

-- 4. Otorgamos los permisos de uso al rol readwrite
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_contrato_sk_seq TO readwrite;

-- =================================================================================
-- CONFIGURACIÓN PARA DIM_ESTADO_CONTRATO
-- =================================================================================

-- 1. Creamos la secuencia oficial para la tabla de estado de contrato
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_estado_contrato_sk_seq START WITH 1;

-- 2. Le asignamos la secuencia como valor por defecto a SK_DIM_ESTADO_CONTRATO
ALTER TABLE seguro_dw_g26473471.dim_estado_contrato 
ALTER COLUMN sk_dim_estado_contrato SET DEFAULT nextval('seguro_dw_g26473471.dim_estado_contrato_sk_seq');

-- 3. Sincronizamos el contador por si ya existen registros cargados
SELECT setval('seguro_dw_g26473471.dim_estado_contrato_sk_seq', COALESCE(MAX(sk_dim_estado_contrato), 1)) FROM seguro_dw_g26473471.dim_estado_contrato;

-- 4. Otorgamos los permisos de uso al rol readwrite
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_estado_contrato_sk_seq TO readwrite;


-- =================================================================================
-- CONFIGURACIÓN PARA DIM_SUCURSAL
-- =================================================================================

-- 1. Creamos la secuencia oficial para la tabla de sucursales
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_sucursal_sk_seq START WITH 1;

-- 2. Le asignamos la secuencia como valor por defecto a SK_DIM_SUCURSAL
ALTER TABLE seguro_dw_g26473471.dim_sucursal 
ALTER COLUMN sk_dim_sucursal SET DEFAULT nextval('seguro_dw_g26473471.dim_sucursal_sk_seq');

-- 3. Sincronizamos el contador por si ya existen registros cargados
SELECT setval('seguro_dw_g26473471.dim_sucursal_sk_seq', COALESCE(MAX(sk_dim_sucursal), 1)) FROM seguro_dw_g26473471.dim_sucursal;

-- 4. Otorgamos los permisos de uso al rol readwrite
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_sucursal_sk_seq TO readwrite;


-- =================================================================================
-- CONFIGURACIÓN PARA DIM_SINIESTRO
-- =================================================================================

-- 1. Creamos la secuencia oficial para la tabla de siniestros
CREATE SEQUENCE IF NOT EXISTS seguro_dw_g26473471.dim_siniestro_sk_seq START WITH 1;

-- 2. Le asignamos la secuencia como valor por defecto a SK_DIM_SINIESTRO
ALTER TABLE seguro_dw_g26473471.dim_siniestro 
ALTER COLUMN sk_dim_siniestro SET DEFAULT nextval('seguro_dw_g26473471.dim_siniestro_sk_seq');

-- 3. Sincronizamos el contador por si ya existen registros cargados
SELECT setval('seguro_dw_g26473471.dim_siniestro_sk_seq', COALESCE(MAX(sk_dim_siniestro), 1)) FROM seguro_dw_g26473471.dim_siniestro;

-- 4. Otorgamos los permisos de uso al rol readwrite
GRANT USAGE, SELECT, UPDATE ON SEQUENCE seguro_dw_g26473471.dim_siniestro_sk_seq TO readwrite;


\copy (SELECT '1') TO '/docker-entrypoint-initdb.d/semaforo.txt';

