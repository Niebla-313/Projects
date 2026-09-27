# ==========================================
# Taller 5
# Alumno: Anthony Alvarado 27.321.522
# ==========================================
#Librerias:
import numpy as np 
import matplotlib.pyplot as plt

# ==========================================
#Codigo:
# ==========================================
#Funciones:
# ==========================================

def SEIR_B(t, y , beta_base, sigma, gamma, N):
	"""
		Modelo SEIR para el escenario B.

		Si el tiempo t>=30, el parametro de transmisión beta se reduce a 0.25
	"""

	S, E, I ,R = y 

	if t >= 30:

		beta = 0.25
	else:
		beta = beta_base

	#Se desarrolla las ecuaciones del modelo SEIR
	dS_dt = -beta * S * I / N
	dE_dt = (beta * S * I / N) - (sigma * E)
	dI_dt = (sigma * E) - (gamma * I)
	dR_dt = gamma * I

	#Se retorna las derivadas.
	return np.array([dS_dt, dE_dt, dI_dt, dR_dt], dtype=float)


def SEIR_A(t, y, beta, sigma, gamma, N):
	"""
		Modelo SEIR para el Escenario A (Libre).
	"""
	S, E, I, R = y

	dS_dt = -beta * S * I / N

	dE_dt = (beta * S * I / N) - (sigma * E)

	dI_dt = (sigma * E) - (gamma * I)

	dR_dt = gamma * I

	return np.array([dS_dt, dE_dt, dI_dt, dR_dt], dtype=float)



def RK4(f, t, y, h, beta, sigma, gamma, N):
	"""
		Implementacion del algoritmo de RK4 para sistemas de EDO.
	"""

	k1 = f(t, y, beta, sigma, gamma, N)

	k2 = f(t + h / 2.0, y + (h / 2.0) * k1, beta, sigma, gamma, N)

	k3 = f(t + h / 2.0, y + (h / 2.0) * k2, beta, sigma, gamma, N)

	k4 = f(t + h, y + h * k3, beta, sigma, gamma, N)

	y_next = y + (h / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4)

	return y_next
		

def inicio_simulacion(deriv_func, beta_val, t_end=160.0, h=0.1):
	"""
		Configura las condiciones inciales y ejecuta la simulación.
	"""
	N = 3e7 #Población total.
	I0 = 100.0 #Infectados iniciales.
	E0 = 0.0 #Expuestos iniciales
	R0 = 0.0 #Recuperados iniciales
	S0 = N - I0 #Susceptibles iniciales
	y0 = np.array([S0, E0, I0, R0], dtype=float)

	# Parámetros biológicos fijos del modelo
	sigma = 0.2  # Tasa de paso de expuesto a infectado
	gamma = 0.1  # Tasa de recuperación

	t_values = np.arange(0.0, t_end + h, h)
	results = np.zeros((len(t_values), 4))
	results[0] = y0

	y = y0
	for i in range(1, len(t_values)):
		t = t_values[i - 1]
		y = RK4(deriv_func, t, y, h, beta_val, sigma, gamma, N)
		results[i] = y

	return t_values, results

# ==========================================
# Bloque Principal:
# ==========================================
# Ejecucion de ambos escenarios
t_A, res_A = inicio_simulacion(SEIR_A, beta_val=0.6)
t_B, res_B = inicio_simulacion(SEIR_B, beta_val=0.6)

# Limpieza preventiva de valores numéricos extremos.
res_A = np.nan_to_num(res_A)
res_B = np.nan_to_num(res_B)

# --- Analisis de conservación (Cálculo de desviaciones) ---
total_pop_A = np.sum(res_A, axis=1)
total_pop_B = np.sum(res_B, axis=1)

max_dev_A = np.max(np.abs(total_pop_A - 3e7))
max_dev_B = np.max(np.abs(total_pop_B - 3e7))


# ==========================================
# Graficas:
# ==========================================

fig = plt.figure(figsize=(14, 6))
fig.set_layout_engine("none") #Evita conflictos de diseño de ventanas (me estaba dando).

ax1 = fig.add_subplot(1, 2, 1)
ax2 = fig.add_subplot(1, 2, 2)

# --- Subgráfico Escenario A ---
ax1.plot(t_A, res_A[:, 0], label="Susceptibles (S)", color="blue")
ax1.plot(t_A, res_A[:, 1], label="Expuestos (E)", color="orange")
ax1.plot(
    t_A, res_A[:, 2], label="Infectados (I)", color="red", linewidth=2
)
ax1.plot(t_A, res_A[:, 3], label="Recuperados (R)", color="green")
ax1.set_title("Escenario A: Libre (Beta = 0.6)")
ax1.set_xlabel("Tiempo (días)")
ax1.set_ylabel("Población")
ax1.set_xlim(0, 160)
ax1.set_ylim(-1000, 32000000)
ax1.grid(True, linestyle="--", alpha=0.6)
ax1.legend()


# Cuadro de desviación máxima en Escenario A.
ax1.text(
    0.5,
    -0.22,
    f"Desviación máxima: {max_dev_A:.2e}",
    transform=ax1.transAxes,
    ha="center",
    fontsize=10,
    bbox=dict(boxstyle="round,pad=0.4", facecolor="#f0f0f0", alpha=0.9),
)

# --- Subgráfico Escenario B ---
ax2.plot(t_B, res_B[:, 0], label="Susceptibles (S)", color="blue")
ax2.plot(t_B, res_B[:, 1], label="Expuestos (E)", color="orange")
ax2.plot(
    t_B, res_B[:, 2], label="Infectados (I)", color="red", linewidth=2
)
ax2.plot(t_B, res_B[:, 3], label="Recuperados (R)", color="green")
ax2.axvline(
    x=30,
    color="black",
    linestyle=":",
    alpha=0.7,
    label="Intervención (t=30, Beta=0.25)",
)
ax2.set_title("Escenario B: Intervención en t=30")
ax2.set_xlabel("Tiempo (días)")
ax2.set_ylabel("Población")
ax2.set_xlim(0, 160)
ax2.set_ylim(-1000, 32000000)
ax2.grid(True, linestyle="--", alpha=0.6)
ax2.legend()

# Cuadro con desviación máxima en Escenario B.
ax2.text(
    0.5,
    -0.22,
    f"Desviación máxima: {max_dev_B:.2e}",
    transform=ax2.transAxes,
    ha="center",
    fontsize=10,
    bbox=dict(boxstyle="round,pad=0.4", facecolor="#f0f0f0", alpha=0.9),
)

# Ajuste de márgenes para acomodar los cuadros de texto inferiores
fig.subplots_adjust(bottom=0.2)
# Mostrar la ventana gráfica
plt.show()

