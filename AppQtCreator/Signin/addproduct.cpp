#include "addproduct.h"
#include "ui_addproduct.h"

AddProduct::AddProduct(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddProduct)
{
    ui->setupUi(this);
}

AddProduct::~AddProduct()
{
    delete ui;
}


QByteArray FinalDataToSave ;
QString ImagePath;

void AddProduct::on_pushButton_Browse_Image_clicked()
{
    ImagePath = QFileDialog::getOpenFileName(this,tr("Select Image"),QCoreApplication::applicationDirPath(),tr("JPG Files (*.jpg)"));
    QPixmap Image(ImagePath);

    QBuffer ImageBufferData;
    if (ImageBufferData.open(QIODevice::ReadWrite))
    {
        Image.save(&ImageBufferData, "JPG");
    }
    FinalDataToSave = ImageBufferData.buffer().toBase64();


    QSqlDatabase::database().transaction();
    ui->lbl_Image_Browse->setPixmap(Image);
}


void AddProduct::on_btnAdd_clicked()
{
    ui->lblInfo->setText("");
    QString sName = ui->txtName->text();
    QString sQuantity = ui->txtQuantity->text();
    QString sStatus = ui->cmbStatus->currentText();
    QString sID = ui->txtID->text();
    QString sPurchasePrice = ui->txtPurchasePrice->text();

    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QSqlQuery QuerySaveImage(MyDB::getInstance()->getDBInstance());

    QuerySaveImage.clear();
    QuerySaveImage.bindValue(":Image_Data",FinalDataToSave);
    query.prepare("insert into Product(productId, productName, productPrice, productQuantity, productStatus,productImage) values ('" +sID +"','" +sName + "','"+ sPurchasePrice + "','"+ sQuantity + "','" + sStatus +"','"+FinalDataToSave+"')");


    // QuerySaveImage.prepare("INSERT INTO Product(productImage)VALUES(:Image_Data)");//
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->lblInfo->setText("Unable to Add Item");
    }
    else
    {
        if(query.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< query.lastQuery();
            ui->lblInfo->setText("Item Added Successfully!");
        }
        else
            qDebug() <<"Unable to Add new Item";
    }



    if(!QuerySaveImage.exec())
    {
        qDebug() << QuerySaveImage.lastError().text() << QuerySaveImage.lastQuery();
        return;
    }
    else{
        QSqlDatabase::database().commit();

        // qDebug() << "Image name:" << sName;
    }
}




