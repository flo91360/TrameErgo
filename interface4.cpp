#include "interface4.h"
#include "ui_interface4.h"
#include "patient.h"
#include "questionnaire.h"
#include "interface4_7.h"

#include <QJsonArray>
#include <QLabel>
#include <QRadioButton>

Interface4::Interface4(int numero, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4)
    , numeroDomaine(numero)
    , domaine(Questionnaire::valeur("otHope/domaines").toArray().at(numero).toObject())
{
    ui->setupUi(this);

    const QString titre = domaine.value("titre").toString();
    ui->labelTitre->setText("OT Hope : " + titre);
    setWindowTitle("TrameErgo - OT Hope : " + titre);

    // Une colonne par réponse possible, « rien à signaler » d'abord.
    const QStringList colonnes = QStringList(Questionnaire::valeur("otHope/neutre").toString())
                                 + Questionnaire::liste("otHope/niveaux");
    for (int colonne = 0; colonne < colonnes.size(); ++colonne) {
        auto *entete = new QLabel("<b>" + colonnes[colonne] + "</b>");
        entete->setAlignment(Qt::AlignCenter);
        ui->grilleActivites->addWidget(entete, 0, colonne + 1);
    }

    const QJsonArray activites = domaine.value("activites").toArray();
    for (int ligne = 0; ligne < activites.size(); ++ligne) {
        ui->grilleActivites->addWidget(new QLabel(activites[ligne].toString()), ligne + 1, 0);
        auto *reponse = new QButtonGroup(this);
        for (int colonne = 0; colonne < colonnes.size(); ++colonne) {
            auto *bouton = new QRadioButton();
            bouton->setToolTip(colonnes[colonne]);
            reponse->addButton(bouton, colonne);
            ui->grilleActivites->addWidget(bouton, ligne + 1, colonne + 1, Qt::AlignCenter);
        }
        // Par défaut rien à signaler : une réponse se corrige en revenant à cette colonne.
        reponse->button(0)->setChecked(true);
        reponses << reponse;
    }
    ui->grilleActivites->setColumnStretch(0, 1);
}

Interface4::~Interface4()
{
    delete ui;
}

void Interface4::on_pushButtonSuivant_clicked()
{
    const QString id = domaine.value("id").toString();
    const QJsonArray niveaux = Questionnaire::valeur("otHope/niveaux").toArray();
    const QJsonArray activites = domaine.value("activites").toArray();

    // Patient::otHope["aide_maison"] = activités de la maison faites avec aide, etc.
    for (const QJsonValue &niveau : niveaux)
        Patient::otHope.remove(niveau.toObject().value("id").toString() + "_" + id);
    for (int i = 0; i < reponses.size(); ++i) {
        const int choix = reponses[i]->checkedId();
        if (choix > 0)
            Patient::otHope[niveaux[choix - 1].toObject().value("id").toString() + "_" + id]
                << activites[i].toString();
    }

    // Next interface : domaine suivant, puis choix des objectifs
    QDialog *suivant;
    if (numeroDomaine + 1 < Questionnaire::valeur("otHope/domaines").toArray().size())
        suivant = new Interface4(numeroDomaine + 1);
    else
        suivant = new Interface4_7();
    this->hide();
    suivant->show();
}
