# Contol via Homebridge

Install `homebridge-better-http-rgb`, and you can use Sklite with this configuartion:

```json
{
    "accessory": "HTTP-RGB",
    "name": "Sklite",
    "service": "Light",
    "switch": {
        "status": "http://<SKLITE IP>",
        "powerOn": "http://<SKLITE IP>/?on=1",
        "powerOff": "http://<SKLITE IP>/?on=0"
    },
    "color": {
        "status": "http://<SKLITE IP>/color",
        "url": "http://<SKLITE IP>/color?set=%s"
    }
}
```