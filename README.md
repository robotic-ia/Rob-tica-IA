# Rob-tica-IA
Proyecto de robótica educativa con IA
1.	Se importan las bibliotecas necesarias: NumPy para operaciones numéricas y Matplotlib para trazar gráficos.
2.	Se define la clase RedNeuronal que representa la red neuronal. La función __init__ inicializa la red neuronal con la estructura de capas dada en layers y la función de activación especificada. Se inicializan los pesos de manera aleatoria dentro del rango [-1, 1]. También se inicializan las listas de pesos y deltas vacías, y se guarda la tasa de aprendizaje en el atributo learning_rate.
3.	Se definen las funciones de activación sigmoid y tanh, así como sus derivadas sigmoid_derivada y tanh_derivada. Estas funciones son utilizadas para calcular las salidas de las neuronas y sus derivadas respectivamente.
4.	Se define el método fit que entrena la red neuronal utilizando el algoritmo de retropropagación (backpropagation). Recibe los datos de entrada X y las etiquetas y como argumentos. Se añade una columna de unos a los datos de entrada para representar el término de sesgo. Se ejecutan epochs iteraciones del entrenamiento.
5.	Dentro del bucle de entrenamiento, se selecciona un ejemplo de forma aleatoria. Se calculan las salidas de cada capa utilizando las funciones de activación y se almacenan en la lista a.
6.	Se calcula el error entre la salida obtenida y la etiqueta correspondiente. A continuación, se calcula el delta (la derivada del error con respecto a la salida de la capa) de la capa de salida.
7.	Se calculan los deltas de las capas ocultas utilizando la retropropagación del error. Los deltas se almacenan en la lista deltas en orden inverso.
8.	Se actualizan los pesos de cada capa utilizando los deltas y el algoritmo de gradiente descendente. Los pesos se actualizan multiplicando el delta de cada capa por la transposición de la capa anterior y luego multiplicando por la tasa de aprendizaje.
9.	Se imprime el progreso del entrenamiento cada 10,000 épocas.
10.	Se define el método predict que realiza una predicción para una entrada x dada. Calcula las salidas de cada capa utilizando las funciones de activación y devuelve la salida de la última capa.
11.	Se define el método get_deltas que devuelve los deltas calculados durante el entrenamiento.
12.	Se crea una instancia de la clase RedNeuronal con una estructura de capas [2, 3, 4] y función de activación "tanh".
13.	Se definen los datos de entrenamiento X y las etiquetas correspondientes y.
14.	Se llama al método fit para entrenar la red neuronal utilizando los datos de entrenamiento y las etiquetas. Se especifica un número de épocas de entrenamiento de 80,001.
15.	Se define la función valNN que redondea y toma el valor absoluto de un número.
16.	Se itera sobre los ejemplos de entrada X y se realiza una predicción utilizando el método predict de la red neuronal. Se muestra la entrada, el valor esperado y el valor obtenido de la predicción.
17.	Se obtienen los deltas calculados durante el entrenamiento y se calcula el costo sumando los elementos correspondientes de cada delta.
18.	Se traza el costo a lo largo de las épocas utilizando Matplotlib.
19.	Se define la función to_str que convierte una matriz NumPy en una cadena de texto en el formato adecuado para el código Arduino.
20.	Se obtienen los pesos de la red neuronal y se imprimen en el formato de código Arduino utilizando la función to_str.
