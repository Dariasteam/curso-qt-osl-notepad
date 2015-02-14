#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Súper editor de texto"));  //función tr para poder realizar traducciones a posteriori
    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);
    barra_ = new QToolBar(this);

    mnuArchivo_ = new QMenu(tr("&Archivo"), this);      //Título y padre
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);
    barra_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);
    barra_->addAction(actArchivoGuardar_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    mnuArchivo_->addAction(actArchivoSalir_);
    barra_->addAction(actArchivoSalir_);

    negrita_ = new QAction(tr("Negrita"), this);
    cursiva_ = new QAction(tr("Cursiva"), this);
    subrayado_ = new QAction(tr("Subrayado"), this);
    color_ = new QAction(tr("Color"), this);
    negrita_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    cursiva_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    subrayado_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
    barra_->addAction(negrita_);
    barra_->addAction(cursiva_);
    barra_->addAction(subrayado_);
    barra_->addAction(color_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarRehacer_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    AcercaDe_ = new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(AcercaDe_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    //Agregamos la barra de menú a la ventana
    this->setMenuBar(mainMenu_);    //this innecesario en este caso
    addToolBar(barra_);

    //Inicializamos el editor de texto
    txtEditor_ = new QTextEdit(this);

    //Conectamos las acciones de los menús con nuestros slots
    //Conectar acción-señal-conquién-conquéslot
    connect(actArchivoAbrir_,   SIGNAL(triggered()), this,          SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this,          SLOT(alGuardar()));
    connect(actArchivoSalir_, SIGNAL(triggered()), this,          SLOT(alSalir()));
    connect(AcercaDe_, SIGNAL(triggered()), this,          SLOT(acercade()));
    connect(actEditarCopiar_,   SIGNAL(triggered()), txtEditor_,    SLOT(copy()));          //esta conecta con un objeto de qt
    connect(actEditarCortar_,   SIGNAL(triggered()), txtEditor_,    SLOT(cut()));
    connect(actEditarPegar_,    SIGNAL(triggered()), txtEditor_,    SLOT(paste()));
    connect(actEditarDeshacer_,    SIGNAL(triggered()), txtEditor_,    SLOT(undo()));
    connect(actEditarRehacer_,    SIGNAL(triggered()), txtEditor_,    SLOT(redo()));
    connect(actFormatoFuente_,  SIGNAL(triggered()), this,          SLOT(alFuente()));

    connect(negrita_,  SIGNAL(triggered()), this,      SLOT(setBold()));
    connect(subrayado_,  SIGNAL(triggered()), this,      SLOT(setUnderline()));
    connect(cursiva_,  SIGNAL(triggered()), this,      SLOT(setItalic()));
    connect(color_,  SIGNAL(triggered()), this,      SLOT(cambiarColor()));


    //Agregamos el editor de texto a la ventana
    setCentralWidget(txtEditor_);
}

NotepadWindow::~NotepadWindow()
{
    //Liberamos los recursos con el propio recolector de Qt, en este caso innecesario ya que todos tienen padre
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    actArchivoSalir_ ->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    actEditarCortar_->deleteLater();
    actEditarDeshacer_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
}

void NotepadWindow::alAbrir()
{
    //Mostramos un dialogo de apertura de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::ReadOnly)) {
            //Si se pudo abrir el archivo, lo leemos y colocamos su contenido en nuestro editor
            txtEditor_->setPlainText(archivo.readAll());    //No hace falta especificar la conversión de qbytearray a qstring porque ya está decarado un constructor que lo sabe hacer e
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alGuardar()
{
    //Mostramos un dialogo de guardado de ficheros y almacenamos la selección (ruta) en una variable
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if (nombreArchivo != "") {
        //Intentamos abrir el archivo
        QFile archivo;
        if(!nombreArchivo.endsWith(".txt")){
            nombreArchivo += ".txt";
        }
        archivo.setFileName(nombreArchivo);
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            //Si se pudo abrir el archivo, escribimos el contenido del editor
            archivo.write(txtEditor_->toPlainText().toUtf8());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        //txtEditor_->setFont(font);
        txtEditor_->setCurrentFont(font);
    }
}

void NotepadWindow::setBold(){
    if(txtEditor_->fontWeight()==86){
        txtEditor_->setFontWeight(50);
    }else{
        txtEditor_->setFontWeight(86);
    }
}

void NotepadWindow::setUnderline(){
  txtEditor_->setFontUnderline(!txtEditor_->fontUnderline());
}

void NotepadWindow::setItalic(){
  txtEditor_->setFontItalic(!txtEditor_->fontItalic());
}

void NotepadWindow::cambiarColor(){

}

void NotepadWindow::alSalir(){
    close();
}

void NotepadWindow::acercade(){
    QMessageBox Ayuda;
    Ayuda.setText("Esta es la ayuda");
    Ayuda.exec();
}
