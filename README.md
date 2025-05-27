Detector de Vazamentos com ESP32  
Projeto desenvolvido para a Faculdade Mackenzie usando IoT.  

Funcionalidades  
- Monitoramento em tempo real de umidade e fluxo de água  
- Alertas via MQTT e acionamento de relé  

Links Úteis  
- [Vídeo de Demonstração](https://youtu.be/MBHQsjjp3Tc?si=GLSnhF7o2RGtjAq6)

Hardware  
| Componente   | Pino ESP32 |  
|--------------|-----------|  
| Sensor YL-69 | GPIO 34   |  
| Sensor YF-S201| GPIO 12   |  
| Relé         | GPIO 5    |  

Simulação no Wokwi
O código usado para simulação está em (https://wokwi.com/projects/432063705287955457) 

**Diferenças para o projeto físico**:  
- Pinos virtuais (ex: `BOTAO_FLUXO = 2` no Wokwi vs. `GPIO 12` no hardware real)  
- Wi-Fi fixo (`Wokwi-GUEST`) vs. configuração personalizável  
