SerialLogHandler logHandler;

String mode = "dev";

void setup()
{
  Log.info("System version: %s", (const char *)System.version());
  Log.info("Starting sensor...");

  Particle.variable("mode", mode);
}

void loop()
{
  checkMode();
}

/*
DO NOT SET TO PROD!!!
*/
void checkMode()
{
  if (mode == "dev")
  {
    SYSTEM_MODE(AUTOMATIC);
    if (!System.updatesEnabled())
    {
      System.enableUpdates();
    }
    if (!WiFi.ready())
    {
      WiFi.on();
      WiFi.connect();
    }
    if (!Particle.connected())
    {
      Particle.connect();
    }
  }
  else if (mode == "prod")
  {
    SYSTEM_MODE(MANUAL);
    WiFi.off();
    System.disableUpdates();
  }
  else
  {
    Log.warn("Invalid mode attempted: %s", mode);
  }
}