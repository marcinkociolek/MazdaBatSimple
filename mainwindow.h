#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <boost/filesystem.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //boost::filesystem::path QMaZdaFolder;
    //boost::filesystem::path ImageFolder;
    //boost::filesystem::path ROIFolder;
    //boost::filesystem::path OptionsFolder;
    //boost::filesystem::path MzFeaturesOutFolder;
    //boost::filesystem::path ClassyfiersFolder;
    //boost::filesystem::path ClassyfiersOptionFile;
    //boost::filesystem::path PredictorOutputFolder;
    //boost::filesystem::path BatFolder;

    //std::string OutFilePrefix;
    //std::string BatFileName;
    //std::string FilePattern;

    std::vector<std::wstring> ImageFileNamesVector;
    std::vector<std::wstring> ROIFileNamesVector;
    std::vector<std::wstring> OptionsFileNamesVector;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool ReloadPaths();
    bool OpenQMaZdaFolder();
    bool OpenImageFolder();
    bool OpenROIFolder();
    bool OpenOptionsFolder();
    bool OpenMzFeauresFolder();
    bool OpenBatFolder();
    void CreateBat();

private slots:
    void on_pushButtonOpenQMaZdaFolder_clicked();

    void on_pushButtonUpenImageFolder_clicked();

    void on_pushButtonOpenRoiFolder_clicked();

    void on_pushButtonOpenOptionsFolder_clicked();

    void on_pushButtonOpenMzFeaturesOutFolder_clicked();

    void on_pushButtonOpenBatFolder_clicked();

    void on_pushButtonClearOut_clicked();

    void on_pushButtonReload_clicked();

    void on_pushButtonCreateBatFile_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
