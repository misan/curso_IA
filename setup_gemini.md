# Guía de Instalación: Gemini-CLI y Arduino-CLI

Este documento detalla los pasos necesarios para instalar y configurar **Gemini-CLI** (el asistente de IA de Google para la terminal) y **Arduino-CLI** (la herramienta de línea de comandos oficial de Arduino) en sistemas Windows y macOS.

---

## 1. Instalación de Gemini-CLI

Gemini-CLI está basado en Node.js, por lo que el proceso es muy similar en ambos sistemas operativos.

### Requisitos previos
* Debes tener instalado **Node.js** (versión 18 o superior). Si no lo tienes, descárgalo e instálalo desde [nodejs.org](https://nodejs.org/).

### Instalación en Windows
Abre tu terminal (PowerShell o Símbolo del sistema) y ejecuta el gestor de paquetes de Node (`npm`) para instalarlo globalmente:

```bash
npm install -g @google/gemini-cli
```
*(Nota: Si prefieres probarlo sin instalarlo permanentemente, puedes usar `npx @google/gemini-cli`).*

### Instalación en macOS
Tienes dos opciones recomendadas:

**Opción A: Usando Homebrew (Recomendada)**
```bash
brew install gemini-cli
```

**Opción B: Usando npm (si prefieres mantenerlo en el ecosistema Node)**
```bash
npm install -g @google/gemini-cli
```

### Prueba y Primeros Pasos
Para verificar la instalación y vincular tu cuenta, ejecuta:
```bash
gemini
```
El sistema abrirá tu navegador web para que inicies sesión con tu cuenta de Google y generará automáticamente las credenciales necesarias para funcionar desde la terminal.

---

## 2. Instalación de Arduino-CLI

Arduino-CLI es un binario independiente. Usaremos los gestores de paquetes nativos o más populares de cada sistema.

### Instalación en Windows
La forma más directa en Windows 10 y 11 es a través de `winget` (el gestor de paquetes de Microsoft). Abre PowerShell y ejecuta:

```bash
winget install ArduinoSA.CLI
```

### Instalación en macOS
La vía estándar y más limpia en macOS es utilizando **Homebrew**. Abre la aplicación Terminal y ejecuta:

```bash
brew install arduino-cli
```

### Prueba y Primeros Pasos
1. **Verificar la instalación:** Comprueba que el sistema reconoce el comando y muestra la versión instalada:
   ```bash
   arduino-cli version
   ```

2. **Actualizar el índice:** Antes de instalar placas o compilar código, es fundamental actualizar el índice local de repositorios de Arduino. Ejecuta:
   ```bash
   arduino-cli core update-index
   ```

---

*Documentación generada y actualizada para la configuración inicial de entornos de desarrollo.*