#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include <string>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

using namespace boost;
using namespace std;
using namespace boost::filesystem;


//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//          My functions outside the Mainwindow class
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void ReadFolder(boost::filesystem::path FileFolder, std::vector<std::wstring> *FileNamesVector, QString FilePaternStr = ".+")
{
    FileNamesVector->clear();
    if (!exists(FileFolder))
    {
        return;
    }
    if (!is_directory(FileFolder))
    {
        return;
    }
    wregex FilePattern(FilePaternStr.toStdWString());
    for (directory_entry& FileToProcess : directory_iterator(FileFolder))
    {

        if (!regex_match(FileToProcess.path().filename().wstring(), FilePattern ))
            continue;
        path PathLocal = FileToProcess.path();

        FileNamesVector->push_back(PathLocal.filename().wstring());
    }
    std::sort(FileNamesVector->begin(),FileNamesVector->end());
}
//------------------------------------------------------------------------------------------------------------------------------
QString StringVectorToQString(std::vector<std::wstring> FileNamesVector)
{
    QString OutStr = "";
    if(FileNamesVector.empty())
        return OutStr;
    for(vector<wstring>::iterator iFileNamesVector = FileNamesVector.begin(); iFileNamesVector != FileNamesVector.end(); iFileNamesVector++)
    {
        OutStr += QString::fromStdWString(*iFileNamesVector) + "\n";
    }

    return OutStr;
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//          Constructor Destructor
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReloadPaths();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//          My functions in the Mainwindow class
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
bool MainWindow::ReloadPaths()
{
    if(!OpenQMaZdaFolder())
        return false;
    if(!OpenImageFolder())
        return false;
    if(!OpenROIFolder())
        return false;
    if(!OpenOptionsFolder())
        return false;
    if(!OpenMzFeauresFolder())
        return false;
    //OpenClassyfiersFolder();
    //OpenClassyfiersOptionsFile();
    //OpenPredictorOutputFotder();
    if(!OpenBatFolder())
        return false;

    return true;
}
bool MainWindow::OpenQMaZdaFolder()
{
    path QMaZdaFolder = path(ui->lineEditMaZdaFolder->text().toStdWString());

    if (!exists(QMaZdaFolder))
    {
        ui->textEditOut->append("QMaZda folder : " + QString::fromStdWString(QMaZdaFolder.wstring())
                                + " not exists ");
        return false;
    }
    if (!is_directory(QMaZdaFolder))
    {
        ui->textEditOut->append("QMaZda folder : " + QString::fromStdWString(QMaZdaFolder.wstring())
                                + " This is not a directory path ");
        return false;
    }
    ui->lineEditMaZdaFolder->setText(QString::fromStdWString(QMaZdaFolder.wstring()));
    path MZGeneratorPath = QMaZdaFolder;
    MZGeneratorPath.append("MzGenerator.exe");
    if (!exists(MZGeneratorPath))
    {
        ui->textEditOut->append("File : " + QString::fromStdWString(MZGeneratorPath.wstring())
                                + " not exists ");
        return false;
    }

    return true;
    /*
    path MzTrainerPath = QMaZdaFolder;
    MzTrainerPath.append("MzTrainer.exe");
    if (!exists(MzTrainerPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MzTrainerPath.string()+ " not exists "));
    }
    path MzPredictPath = QMaZdaFolder;
    MzPredictPath.append("MzPredict.exe");
    if (!exists(MzPredictPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MzPredictPath.string()+ " not exists "));
    }
*/
}
//------------------------------------------------------------------------------------------------------------------------------
bool MainWindow::OpenImageFolder()
{
    path ImageFolder = path(ui->lineEditImageFolder->text().toStdWString());

    ImageFileNamesVector.clear();
    ui->textEditImageFiles->clear();

    if (!exists(ImageFolder))
    {
        ui->textEditOut->append("Image folder : " + QString::fromStdWString(ImageFolder.wstring())
                                + " not exists ");
        return false;
    }
    if (!is_directory(ImageFolder))
    {
        ui->textEditOut->append(" Image folder : " + QString::fromStdWString(ImageFolder.wstring())
                                + " This is not a directory path ");
        return false;
    }
    ReadFolder(ImageFolder, &ImageFileNamesVector, ui->lineEditImageFilePattern->text() );

    ui->textEditImageFiles->append(StringVectorToQString(ImageFileNamesVector));
    return true;
}
//------------------------------------------------------------------------------------------------------------------------------
bool MainWindow::OpenROIFolder()
{
    path ROIFolder = path(ui->lineEditROIFolder->text().toStdWString());
    if (!exists(ROIFolder))
    {
        ui->textEditOut->append("ROI folder : " + QString::fromStdWString(ROIFolder.wstring())
                                + " not exists ");
        return false;
    }
    if (!is_directory(ROIFolder))
    {
        ui->textEditOut->append(" Image folder : " + QString::fromStdWString(ROIFolder.wstring())
                                + " This is not a directory path ");
        return false;
    }

    path ROIFile = ROIFolder.append(ui->lineEditROIFileName->text().toStdWString());
    if (!exists(ROIFile) && !ui->checkBoxRoiNameSameAsImage->checkState())
    {
        ui->textEditOut->append("ROI file : " + QString::fromStdWString(ROIFile.wstring())
                                + " not exists ");
        return false;
    }
    return true;
    //ReadFolder(ROIFolder, &ROIFileNamesVector, ui->lineEditROIFilePattern->text().toStdString() );
    //ui->textEditROIFiles->append(QString::fromStdString(StringVectorToString(ROIFileNamesVector)));
}
//------------------------------------------------------------------------------------------------------------------------------
bool MainWindow::OpenOptionsFolder()
{
    path OptionsFolder = path(ui->lineEditOptionsFolder->text().toStdWString());

    if (!exists(OptionsFolder))
    {
        ui->textEditOut->append("Options folder : " + QString::fromStdWString(OptionsFolder.wstring())
                                + " not exists ");
        return false;
    }
    if (!is_directory(OptionsFolder))
    {
        ui->textEditOut->append(" Options folder : " + QString::fromStdWString(OptionsFolder.wstring())
                                + " This is not a directory path ");
        return false;
    }

    path OptionsFile = OptionsFolder.append(ui->lineEditOptionsFileName->text().toStdWString());
    if (!exists(OptionsFile))
    {
        ui->textEditOut->append("Options file : " + QString::fromStdWString(OptionsFile.wstring())
                                + " not exists ");
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------------------------
bool MainWindow::OpenMzFeauresFolder()
{
    path MzFeaturesOutFolder = path(ui->lineEditMzFeaturesOutFolder->text().toStdWString());

    if (!exists(MzFeaturesOutFolder))
    {
        ui->textEditOut->append("MzFeatutes folder : " + QString::fromStdWString(MzFeaturesOutFolder.wstring())
                                + " not exists ");
        return false;
    }
    if (!is_directory(MzFeaturesOutFolder))
    {
        ui->textEditOut->append(" MzFeatutes folder : " + QString::fromStdWString(MzFeaturesOutFolder.wstring())
                                + " This is not a directory path ");
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------------------------
bool MainWindow::OpenBatFolder()
{
    path BatFolder = path(ui->lineEditBatFolder->text().toStdWString());
    if (!exists(BatFolder))
    {
        ui->textEditOut->append("Bat : " + QString::fromStdWString(BatFolder.wstring())
                                + " not exists ");
        return false;
    }
    if (!is_directory(BatFolder))
    {
        ui->textEditOut->append(" Bat : " + QString::fromStdWString(BatFolder.wstring())
                                + " This is not a directory path ");
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::CreateBat()
{
    ui->textEditOut->clear();
    if(!ReloadPaths())
        return;

    if(ImageFileNamesVector.empty())
        return;

    path MZGeneratorPath = path(ui->lineEditMaZdaFolder->text().toStdWString());
    MZGeneratorPath.append("MzGenerator.exe");

    path ImFolder = path(ui->lineEditImageFolder->text().toStdWString());

    path ROIFile = path(ui->lineEditROIFolder->text().toStdWString());
    ROIFile.append(ui->lineEditROIFileName->text().toStdWString());

    path OptionsFile = path(ui->lineEditOptionsFolder->text().toStdWString());
    OptionsFile.append(ui->lineEditOptionsFileName->text().toStdWString());

    path FeaturesOutFile = path(ui->lineEditMzFeaturesOutFolder->text().toStdWString());
    FeaturesOutFile.append((ui->lineEditOutFilePrefix->text() + ".csv").toStdWString());

    path BatFile = path(ui->lineEditBatFolder->text().toStdWString());
    BatFile.append((ui->lineEditBatFileName->text() + "Feat.bat").toStdWString());

    size_t imagesCount = ImageFileNamesVector.size();

    string BatFileContent = "cls\n";


    BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";
    BatFileContent += "echo \" Test Data\"\n";
    BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";


    path ImFile = ImFolder;
    ImFile.append(ImageFileNamesVector[0]);

    if(ui->checkBoxRoiNameSameAsImage->checkState())
    {
        ROIFile = path(ui->lineEditROIFolder->text().toStdWString());
        ROIFile.append(ImFile.stem().string() + ".roi");
    }


    BatFileContent += MZGeneratorPath.string()
                      + " -m roi -i " + ImFile.string()
                      + " -r " + ROIFile.string()
                      + "    -o " + FeaturesOutFile.string()
                      + " -f " + OptionsFile.string()
                      + "\n";
    for(size_t i = 1; i < imagesCount; i++)
    {
        ImFile = ImFolder;
        ImFile.append(ImageFileNamesVector[i]);

        if(ui->checkBoxRoiNameSameAsImage->checkState())
        {
            ROIFile = path(ui->lineEditROIFolder->text().toStdWString());
            ROIFile.append(ImFile.stem().string() + ".roi");
        }

        BatFileContent += MZGeneratorPath.string()
                          + " -m roi -i " + ImFile.string()
                          + " -r " + ROIFile.string()
                          + " -a -o " + FeaturesOutFile.string()
                          + "\n";
    }
    std::ofstream FileToSave(BatFile.string());
    if (!FileToSave.is_open())
    {
        ui->textEditOut->append(QString::fromStdString("Bat File Not Saved"));
    }
    FileToSave << BatFileContent;
    FileToSave.close();
    BatFileContent.clear();
}
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//          Slots
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_pushButtonOpenQMaZdaFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);

    path tempDir = path(ui->lineEditMaZdaFolder->text().toStdString());
    if(exists(tempDir) && is_directory(tempDir))
    {
        dialog.setDirectory( QString::fromStdString(tempDir.string()));
    }

    if(dialog.exec())
    {
        ui->lineEditMaZdaFolder->setText(dialog.directory().path());
    }
    else
        return;
    OpenQMaZdaFolder();
}

void MainWindow::on_pushButtonUpenImageFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);

    path tempDir = path(ui->lineEditImageFolder->text().toStdString());
    if(exists(tempDir) && is_directory(tempDir))
    {
        dialog.setDirectory( QString::fromStdString(tempDir.string()));
    }

    if(dialog.exec())
    {
        ui->lineEditImageFolder->setText(dialog.directory().path());
        //ImageFolder = dialog.directory().path().toStdWString();
    }
    else
        return;

    OpenImageFolder();
}

void MainWindow::on_pushButtonOpenRoiFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);

    path tempDir = path(ui->lineEditROIFolder->text().toStdString());
    if(exists(tempDir) && is_directory(tempDir))
    {
        dialog.setDirectory( QString::fromStdString(tempDir.string()));
    }

    if(dialog.exec())
    {
        ui->lineEditROIFolder->setText(dialog.directory().path());
        //ROIFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    OpenROIFolder();
}

void MainWindow::on_pushButtonOpenOptionsFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);

    path tempDir = path(ui->lineEditOptionsFolder->text().toStdString());
    if(exists(tempDir) && is_directory(tempDir))
    {
        dialog.setDirectory( QString::fromStdString(tempDir.string()));
    }

    if(dialog.exec())
    {
        ui->lineEditOptionsFolder->setText(dialog.directory().path());
        //OptionsFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    OpenOptionsFolder();
}

void MainWindow::on_pushButtonOpenMzFeaturesOutFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);

    path tempDir = path(ui->lineEditMzFeaturesOutFolder->text().toStdString());
    if(exists(tempDir) && is_directory(tempDir))
    {
        dialog.setDirectory( QString::fromStdString(tempDir.string()));
    }

    if(dialog.exec())
    {
        ui->lineEditMzFeaturesOutFolder->setText(dialog.directory().path());
        //MzFeaturesOutFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    OpenMzFeauresFolder();
}

void MainWindow::on_pushButtonOpenBatFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);

    path tempDir = path(ui->lineEditBatFolder->text().toStdString());
    if(exists(tempDir) && is_directory(tempDir))
    {
        dialog.setDirectory( QString::fromStdString(tempDir.string()));
    }

    if(dialog.exec())
    {
        ui->lineEditBatFolder->setText(dialog.directory().path());
        //BatFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    OpenBatFolder();
}

void MainWindow::on_pushButtonClearOut_clicked()
{
    ui->textEditOut->clear();
}

void MainWindow::on_pushButtonReload_clicked()
{
    ReloadPaths();
}

void MainWindow::on_pushButtonCreateBatFile_clicked()
{
    CreateBat();
}
