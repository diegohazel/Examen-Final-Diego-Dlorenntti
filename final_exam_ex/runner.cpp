#include "runner.h"

// variable global en donde debe guardarse los datos pasados
// Esto para el calculo correcto de los siguientes pasos, distancias, calorias, etc
vector<package> storage_data = {};

// TODO: Implente esta funcion.
// Verifique que la data en el paquete sea valida
bool check_correct_data(package data) { //data se recibe desde main.cpp

  if (data.steps <= 0) {  // Pasos negativos o igual a cero?
    return false;       // Paquete no sirve por illogico
  }
  if (data.segundos < 0) { // ¿Tiempo negativo?
    return false;        // Paquete no sirve illogico
  }
  return true;
  //si pasa las 2 condiciones es valido TRUE si no pasa ya imprimio 0 directamente
}


// TODO: Implemente esta funcion.
// Verifique que el tiempo obtenido sea correcto.
bool check_correct_time(long seconds) {
  // 1. Si no hay datos guardados, el tiempo siempre va a sr valido
  if (storage_data.empty()) {
    return true;
  }

  // 2. Obtener el tiempo del último paquete guardado
  long ultimo_tiempo = storage_data.back().segundos; // Accede solo a 'segundos" del ultimo paquete

  // 3. Comparar el tiempo nuevo con el último tiempo
  if (seconds > ultimo_tiempo) {
    return true;  // VALIDO:el tiempo es mayor
  } else {
    return false; // INVALIDO: el tiempo es menor o igual
  }
}

// TODO: Implemente esta funcion
// Devuelve la suma total de los pasos dados durante el dia
int get_step_day(int steps) {
  int total_pasos = 0; // pasos incian en 0

  // Recorrer storage_data con for
  for (int i = 0; i < storage_data.size(); i++) {
    total_pasos += storage_data[i].steps; // Sumamos los pasos de cada paquete
  }

  total_pasos += steps; // Agrego los pasos del nuevo paquete

  return total_pasos; // devolver el total
  }

// TODO: Implemente esta funcion
// Devuelve la distancia recorrida segun los pasos dados durante el dia
double get_distance(int steps) {
  //formula: distancia(KM) = Pasos * Longitud de Pasos(STEP_M)  /  1000
  double distancia_metros = steps * STEP_M; // Pasos a metros
  double distancia_km = distancia_metros / 1000; // Metros a km
  return distancia_km;
}

// TODO: Implemente esta funcion
// Devuelve las calorias quemadas segun la distancia recurrida
double get_calories_burned(double dist, times current_time) {
  // 1.- Tiempo a horas
  double tiempo_horas = current_time.hour + current_time.min / 60 +
    current_time.sec / 3600;

  // 2.- Calcular velocidad (km/h)
  double velocidad = dist / tiempo_horas;

  // 3.- : Tiempo a minutos
  double tiempo_min = tiempo_horas * 60;

  // 4.- : Formula final
  double calorias = (K_1 * WEIGHT +
                    (velocidad * velocidad / HEIGHT) *
                    K_2 * WEIGHT) *
                    tiempo_min;

  return calorias;
}

// TODO: Implemente esta funcion
// Devuelve una string con el mensaje de motivacion segun la distancia recorrida
string get_achievement(double dist) {
   if (dist >= 6.5) {
    return "¡Gran entrenamiento! Objetivo cumplido.";
  }
  else if (dist >= 3.9) {
    return "¡Nada mal! Hoy ha sido un día productivo.";
  }
  else if (dist >= 2.0) {
    return "Menos que el resultado deseado, ¡pero intenta alcanzarlo mañana!";
  }
  else {
     return "Está bien tomarse el día de descanso. No siempre se puede ganar.";
    }
}

// TODO: Implemente las funciones restantes:
void show_message(times t, int total_steps, double dist, double calories, string msg){
  string tiempo_formateado = format_time(t); //uso la funcion para volver el tiempo a formato

  cout << "Tiempo: " << tiempo_formateado << ".\n";
  cout << "Pasos dados hoy: " << total_steps << ".\n";
  cout << "La distancia fue " << dist << " km.\n";
  cout << "Has quemado " << calories << " cal.\n";
  cout << msg << endl;
}

//????
times get_time_hms(long seconds){
  times t;

  t.hour = seconds / 3600;              // 3600 segundos en una hora
  seconds = seconds % 3600;              // resto despuees de sacar las horas

  t.min = seconds / 60;                  // 60 segundos en un minuto
  t.sec = seconds % 60;                  // lo que queda son los segundos

  return t;
}


string format_time(times t){
  string result = "";

  // horas
  if (t.hour < 10) result += "0";
  result += to_string(t.hour);
  result += ":";

  // minutos
  if (t.min < 10) result += "0";
  result += to_string(t.min);
  result += ":";

  // segundos
  if (t.sec < 10) result += "0";
  result += to_string(t.sec);

  return result;
}



/*
// TODO: Implemente la funcion madre
// Esta funcion debe llamar a las otras para realizar lo indicado en el pdf
vector<package> accept_package(package data) {
  return storage_data;
}    */


vector<package> accept_package(package data) {
  // 1. Validar el paquete
  if (!check_correct_data(data)) {
    cout << "0\n";
    return storage_data;
  }

  // 2. Validar el tiempo
  if (!check_correct_time(data.segundos)) {
    cout << "0\n";
    return storage_data;
  }

  // 3. Guardar el paquete
  storage_data.push_back(data);

  // 4. Obtener total de pasos
  int total_steps = get_step_day(0); // ya se guardó, así que no hay que sumar data.steps

    // 5. Calcular distancia
  double dist = get_distance(total_steps);

   // 6. Obtener hora, minutos, segundos
  times t = get_time_hms(data.segundos);

   // 7. Calcular calorías
  double calories = get_calories_burned(dist, t);

  // 8. Obtener mensaje motivacional
  string msg = get_achievement(dist);

  // 9. Mostrar mensaje final
  show_message(t, total_steps, dist, calories, msg);

   // 10. Devolver datos almacenados
  return storage_data;
}