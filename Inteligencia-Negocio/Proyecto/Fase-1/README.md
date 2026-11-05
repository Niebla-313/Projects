## 🏢 Modelo de Negocio y Procesos Analíticos: Seguros Alta Vista

### 📌 Visión General del Negocio
**Seguros Alta Vista** comercializa y administra pólizas de seguros a través de distintas sucursales. Ante los retos del mercado post-pandemia, la gerencia impulsa una estrategia **Data-Driven** orientada a monitorear la rentabilidad comercial, controlar la siniestralidad, medir la satisfacción del cliente y evaluar el cumplimiento de sus metas presupuestarias.

---

### ⚙️ Procesos de Negocio

Para capturar cuantitativamente la operación en el Data Warehouse mediante la metodología Kimball, la actividad de la empresa se estructura a través de **cuatro procesos de negocio centrales**:

1. **Proceso de Ventas y Contratación (`FACT_REGISTRO_CONTRATO`)**
   * **Descripción:** Registra la actividad de ventas y la suscripción de pólizas. Contiene las métricas de montos y cantidades asociadas a los productos y clientes, vinculadas directamente por el estado actual del contrato (*Activo, Vencido, Suspendido*).

2. **Proceso de Siniestralidad y Reclamos (`FACT_REGISTRO_SINIESTRO`)**
   * **Descripción:** Cuantifica los eventos de siniestralidad y atención de reclamos. Utiliza la técnica de *Role Playing Dimensions* para diferenciar conceptual y temporalmente la fecha de ocurrencia del evento (`fecha_siniestro`) de la fecha de respuesta otorgada por la empresa (`fecha_respuesta`).

3. **Proceso de Evaluación del Servicio (`FACT_EVALUACION_SERVICIO`)**
   * **Descripción:** Mide la satisfacción del cliente al cierre de la vigencia de la póliza. Registra la calificación otorgada por el asegurado hacia un producto específico, impulsada por el programa de incentivos y premios de la empresa.

4. **Proceso de Planificación y Control Strategico (`FACT_METAS`)**
   * **Descripción:** Gestiona la planificación del negocio. Almacena las proyecciones de ventas, renovaciones y clientes esperados, utilizando un rango temporal de vigencia (inicio/fin) para contrastar formalmente la ejecución real frente a la meta establecida.
