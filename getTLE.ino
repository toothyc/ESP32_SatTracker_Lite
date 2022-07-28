void getTLE(int SAT) {
  client.setCACert(root_ca);
  // Make HTTP request and get TLE for satellite//
  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.println("GET https://" + String(server) + startURL + String(satID[SAT]) + " HTTP/1.0");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
        if (line == "\r") {
          break;
        }
    }
    int j = 0;
    while (client.available()) {
      char c = client.read();
      TLE[j] = c;   //store characters to string
      j++;
      
    }
    k = 0;
    for (j = 0; j < 25; j++) { //TLE line 1 spans characters 1 - 25
      satnames[SAT][k] = TLE[j];
      k++;
    }
    k = 0;
    for (j = 26; j < 96; j++) { //TLE line 1 spans characters 26 - 96
      TLE1[SAT][k] = TLE[j];
      k++;
    }
    k = 0;
    for (j = 97; j < 167; j++) { //TLE line 2 spans characters 97 - 167
      TLE2[SAT][k] = TLE[j];
      k++;
    }
    noTLE = false;
    client.stop();
  }  
  Serial.println("Collected data #: " + String(SAT) + " For: " + String(satnames[SAT]));
}

