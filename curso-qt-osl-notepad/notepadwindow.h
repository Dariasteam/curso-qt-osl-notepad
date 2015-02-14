#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
//Incluimos librerias necesarias
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QPlainTextEdit>       //Cuadro de texto plano
#include <QFileDialog>          //VEntana de Abrir-guardar
#include <QFile>                //Clase que permite abrir ficheros
#include <QFontDialog>          //Cuadro de selección de fuente
#include <QClipboard>           //Portapepeles
#include <QKeySequence>         //Accesos directos
#include <QToolBar>
#include <QColor>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT        //Directiva al precompilador de Qt para avisar que hay palabras reservadas de Qt

public:
    NotepadWindow(QWidget *parent = 0); //Tiene padre?
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alSalir();
    void acercade();
    void setBold();
    void setUnderline();
    void setItalic();
    void cambiarColor();

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QMenu*          mnuAyuda_;
    QAction*        actArchivoAbrir_;
    QAction*        AcercaDe_;
    QAction*        actArchivoGuardar_;
    QAction*        actArchivoSalir_;
    QMenu*          mnuFormato_;
    QAction*        actFormatoFuente_;
    QMenu*          mnuEditar_;
    QAction*        actEditarCopiar_;
    QAction*        actEditarPegar_;
    QAction*        actEditarCortar_;
    QAction*        actEditarDeshacer_;
    QAction*        actEditarRehacer_;
    QTextEdit*      txtEditor_;
    QClipboard*     portapapeles_;
    QToolBar*       barra_;
    QAction*        negrita_;
    QAction*        cursiva_;
    QAction*        subrayado_;
    QAction*        color_;


};

#endif // NOTEPADWINDOW_H
