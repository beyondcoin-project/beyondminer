#include "poolparse.h"

PoolParse::PoolParse(QObject *parent) :
    QObject(parent)
{
}

QString PoolParse::getURL(QString poolName, QString apiKey)
{
    QString url;

    if (poolName == "Beyondcoinpool.com")
        url = "https://beyondcoinpool.com/api";
    else if (poolName == "SaltPool")
        url = "https://saltpool.net/api";
    else if (poolName == "0769 Pool")
        url = "https://0769.it/api";
    else if (poolName == "Crypto Pools")
        url = "https://cryptopools.aod-tech.com/api";

    url.append(apiKey);

    return url;
}

QString PoolParse::parseData(QString poolName, QVariantMap data)
{
    QString message;
    double totalRewards = -1;
    double estimatedRewards = -1;
    double paidRewards = -1;
    double unpaidRewards = -1;
    double past24hRewards = -1;

    QVariantMap userMap;

    if (poolName == "Beyondcoinpool.com")
    {
        userMap = data.value("user").toMap();
        totalRewards = userMap.value("total_rewards").toDouble();
        paidRewards = userMap.value("paid_rewards").toDouble();
        unpaidRewards = userMap.value("unpaid_rewards").toDouble();
        past24hRewards = userMap.value("past_24h_rewards").toDouble();
    }
    else if (poolName == "SaltPool")
    {
        unpaidRewards = data.value("current_balance").toDouble();
    }
    else if (poolName == "0769 Pool")
    {
        unpaidRewards = data.value("confirmed_rewards").toDouble();
        paidRewards = data.value("payout_history").toDouble();
        estimatedRewards = data.value("round_estimate").toDouble();
    }
    else if (poolName == "Crypto Pools")
    {
        unpaidRewards = data.value("confirmed_rewards").toDouble();
        paidRewards = data.value("payout_history").toDouble();
        estimatedRewards = data.value("round_estimate").toDouble();
    }

    if (totalRewards != -1)
    {
        QString totalString = QString("<b>Total rewards:</b><br/>%1 BYND<br/><br/>").arg(totalRewards);
        message.append(totalString);
    }
    if (estimatedRewards != -1)
    {
        QString estString = QString("<b>Estimated rewards:</b><br/>%1 BYND<br/><br/>").arg(estimatedRewards);
        message.append(estString);
    }
    if (paidRewards != -1)
    {
        QString paidString = QString("<b>Paid rewards:</b><br/>%1 BYND<br/><br/>").arg(paidRewards);
        message.append(paidString);
    }
    if (unpaidRewards != -1)
    {
        QString unpaidString = QString("<b>Unpaid rewards:</b><br/>%1 BYND<br/><br/>").arg(unpaidRewards);
        message.append(unpaidString);
    }
    if (past24hRewards != -1)
    {
        QString past24hString = QString("<b>Rewards in past 24 hours:</b><br/>%1 BYND<br/><br/>").arg(past24hRewards);
        message.append(past24hString);
    }

    return message;
}
