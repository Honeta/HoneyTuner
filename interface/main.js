const { app, BrowserWindow, Menu } = require('electron')
const { join } = require('path')

function createWindow () {
  const win = new BrowserWindow({
    width: 950,
    height: 750,
    icon:join(__dirname,'../image/icon.ico'),
    resizable: false,
    webPreferences: {
        nodeIntegration: true
    }
  })
  win.loadFile('interface/index.html')
}

app.whenReady().then(createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow()
  }
})

Menu.setApplicationMenu(null)
