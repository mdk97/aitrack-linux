#pragma once

#include <string>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QObject>


class Version
{
public:
	int stage; // alpha, beta or normal
	std::string ver;

	Version(std::string version): stage(10), ver()
	{
		int index_dash = -1;

		for (unsigned int i = 0; i < version.size(); i++) 
		{
			if (version.at(i) == *".")
				continue;
			if (version.at(i) == *"-")
			{
				index_dash = i;
				break;
			}
			ver.push_back(version.at(i));
		}
		
		if (index_dash > 0)
		{
			// Version id contains alpha/beta
			if (version.at(index_dash + 1) == *"a")  // alpha
				stage = 0;
			if (version.at(index_dash + 1) == *"b")  // beta
				stage = 1;
			// Else, its a normal version
		}
	};

    bool operator<(Version const& rhs) const
    {		
		int numbers_comparison = rhs.ver.compare(ver);
		if (numbers_comparison == 0)
		{
			return stage < rhs.stage;
		}
		else 
		{
			return numbers_comparison > 0;
		}
    }
};

class IUpdateSub
{
public:
	/*
	* Callback to check whether a newer version is available.
	*/
	virtual void on_update_check_completed(bool update_exists) = 0;
	virtual ~IUpdateSub();
};



class UpdateChecker : public QObject
{
Q_OBJECT
private:
	QNetworkRequest request;
	QNetworkAccessManager manager;
	IUpdateSub* observer;
	Version current_version;

public:
	~UpdateChecker();
	UpdateChecker(std::string &version, IUpdateSub *obs);
	UpdateChecker(const std::string &&version, IUpdateSub *obs);
	void get_latest_update(std::string &repo);
	void get_latest_update(const std::string &&repo);
	

private slots:
	void callback(QNetworkReply* reply);
};



