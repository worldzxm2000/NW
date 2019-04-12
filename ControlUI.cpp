#include "ControlUI.h"
#include<QMessageBox>
ControlUI::ControlUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowCloseButtonHint | Qt::FramelessWindowHint);
	ui.TitleLabel_Name->setText(QString::fromLocal8Bit("农委"));
	setWindowTitle(QString::fromLocal8Bit("农委设备控制"));
	ui.CloseBtn->setToolTipName(QString::fromLocal8Bit("关闭"));
	ui.MinBtn->setToolTipName(QString::fromLocal8Bit("最小化"));
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
}

ControlUI::~ControlUI()
{
}

void ControlUI::closeEvent(QCloseEvent *event)
{
	QWidget::close();
	*isActive = false;
	delete this;
}

void ControlUI::slot_minWindow()
{
	this->showMinimized();
}

void ControlUI::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void ControlUI::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void ControlUI::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}

void ControlUI::on_RIDBtn_clicked()
{
	cmmIndex = 101;
	//读取ID
	QString Comm = "ID\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_WIDBtn_clicked()
{
	cmmIndex = 102;
	//设置ID
	QString Comm = "ID "+ui.DevicelineEdit->text().trimmed()+"\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_RTimeBtn_clicked()
{
	cmmIndex = 103;
	//读取时钟
	QString Comm = "DATETIME\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_WTimeBtn_clicked()
{
	cmmIndex = 104;
	//设置时钟
	QString Time;
	Time = ui.RdateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss");
	QString Comm = "DATETIME " + Time + "\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_RALTBtn_clicked()
{
	cmmIndex = 105;
	//读取高度
	QString Comm = "ALT\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_WALTBtn_clicked()
{
	cmmIndex = 106;
	//设置高度
	QString Comm = "ALT " + ui.LineEdit_ALT->text().trimmed() + "\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_RLATBtn_clicked()
{
	cmmIndex = 107;
	//读取纬度
	QString Comm = "LAT\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);

}

void ControlUI::on_WLATBtn_clicked()
{
	cmmIndex = 108;
	//设置纬度
	QString Comm = "LAT " + ui.LineEdit_LAT->text().trimmed() + "\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_RLNGBtn_clicked()
{
	cmmIndex = 109;
	//读取经度
	QString Comm = "LONG\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_WLNGBtn_clicked()
{
	cmmIndex = 110;
	//设置经度
	QString Comm = "LONG " + ui.LineEdit_LNG->text().trimmed() + "\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_RRESETBtn_clicked()
{
	cmmIndex = 111;
	//重启采集器
	QString Comm = "RESET\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_RUPDATEBtn_clicked()
{
	cmmIndex = 112;
	//远程升级
	QString Comm = "UPDATE\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

void ControlUI::on_DownBtn_clicked()
{
	cmmIndex = 113;
	//补抄
	QString Time_B, Time_E;
	Time_B = ui.BdateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm");
	Time_E = ui.EdateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm");
	QString Comm = "DMTD " + Time_B + " " + Time_E + "\r\n";
	QByteArray ba = Comm.toLatin1();
	LPCSTR ch = ba.data();
	int len = Comm.length();
	::send(Socket, ch, len, 0);
}

//设备返回值
void ControlUI::setValue(QStringList list)
{
	switch (cmmIndex)
	{
	case 101://设备号
	{
		if (list.count() < 1)
			break;
		ui.DevicelineEdit->setText(list.at(0));
		break;
	}
	case 103://设备时间
	{
		if (list.count() < 2)
			break;
		QString datetime;
		datetime = list.at(0) + " " + list.at(1);
		QDateTime time = QDateTime::fromString(datetime, "yyyy-MM-dd hh:mm:ss");
		ui.RdateTimeEdit->setDateTime(time);
		break;
	}
	case 105://海拔
	{
		if (list.count() < 1)
			break;
		ui.LineEdit_ALT->setText(list.at(0));
		break;
	}
	case 107://纬度
	{
		if (list.count() < 1)
			break;
		ui.LineEdit_LAT->setText(list.at(0));
		break;
	}
	case 109://经度
	{
		if (list.count() < 1)
			break;
		ui.LineEdit_LNG->setText(list.at(0));
		break;
	}
	default:
	{
		if (list.count() < 1)
			break;
		QString r = list.at(0);
		if (r.toUpper().compare("T") == 0)
		{
			QMessageBox::about(this, QString::fromLocal8Bit("设备状态"), QString::fromLocal8Bit("操作成功！"));
		}
		else
		{
			QMessageBox::about(this, QString::fromLocal8Bit("设备状态"), QString::fromLocal8Bit("操作失败！"));
		}
	}
	break;
	}
}

