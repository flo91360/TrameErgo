"""Vérifie que le contenu (contenu/questionnaire.json, contenu/bilan.docx) et le code
de TrameErgo concordent.

Lancé par la CI (job « build ») et en local : python outils/verifier_contenu.py
Contrôles :
- questionnaire.json est lisible et contient chaque chemin lu par le code
  (Questionnaire::liste("…"), valeur("…"), phrase("…", …)) ;
- chaque champ {…} du modèle est remplacé par le code, et inversement. Les
  champs OT Hope {niveau_domaine} (aide_maison…) sont construits par le code à
  partir des identifiants otHope/niveaux et otHope/domaines du questionnaire ;
- le modèle ne contient ni accolade isolée ni ancien champ i_….
"""
import json
import re
import sys
import zipfile
from pathlib import Path

RACINE = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(__file__).resolve().parent.parent
QUESTIONNAIRE = RACINE / "contenu" / "questionnaire.json"
MODELE = RACINE / "contenu" / "bilan.docx"
APPEL_CHAMP = re.compile(r'Word::(?:replaceText|replaceTextFromZoneText)\(\s*"\{(\w+)\}"')
APPEL_QUESTIONNAIRE = re.compile(r'Questionnaire::(?:liste|valeur|phrase)\(\s*"([^"]+)"')


def sources():
    """Fichiers .cpp compilés, lus dans SOURCES du .pro."""
    pro = (RACINE / "TrameErgo.pro").read_text(encoding="utf-8")
    bloc = re.search(r"SOURCES\s*\+=((?:[^\n]*\\\n)*[^\n]*)", pro).group(1)
    return [RACINE / nom for nom in re.findall(r"[\w./-]+\.cpp", bloc)]


def lire_code():
    """{champ: [fichier:ligne]} et {chemin du questionnaire: [fichier:ligne]}."""
    champs, chemins = {}, {}
    for fichier in sources():
        for numero, ligne in enumerate(fichier.read_text(encoding="utf-8").splitlines(), 1):
            if ligne.lstrip().startswith("//"):
                continue
            lieu = f"{fichier.name}:{numero}"
            for champ in APPEL_CHAMP.findall(ligne):
                champs.setdefault(champ, []).append(lieu)
            for chemin in APPEL_QUESTIONNAIRE.findall(ligne):
                chemins.setdefault(chemin, []).append(lieu)
    return champs, chemins


def textes_du_modele():
    """Texte de chaque paragraphe du modèle. Word découpe le texte en morceaux
    <w:t> : on les recolle paragraphe par paragraphe."""
    paragraphes = []
    with zipfile.ZipFile(MODELE) as docx:
        for nom in docx.namelist():
            if not re.fullmatch(r"word/(document|header\d*|footer\d*)\.xml", nom):
                continue
            texte = ""
            for morceau in re.finditer(r"<w:t(?: [^>]*)?>([^<]*)</w:t>|<w:p[ >]|</w:p>|<w:tab/>|<w:br/>",
                                       docx.read(nom).decode("utf-8")):
                if morceau.group(1) is not None:
                    texte += morceau.group(1)
                else:
                    paragraphes.append(texte)
                    texte = ""
            paragraphes.append(texte)
    return [p for p in paragraphes if p]


def main():
    erreurs = []
    try:
        questionnaire = json.loads(QUESTIONNAIRE.read_text(encoding="utf-8"))
    except (OSError, ValueError) as erreur:
        print(f"{QUESTIONNAIRE.relative_to(RACINE)} illisible : {erreur}")
        return 1
    code, chemins = lire_code()

    for chemin, lieux in sorted(chemins.items()):
        valeur = questionnaire
        for cle in chemin.strip("/").split("/"):
            valeur = valeur.get(cle) if isinstance(valeur, dict) else None
        if valeur is None:
            erreurs.append(f"{', '.join(lieux)} : « {chemin} » absent de questionnaire.json.")

    ot_hope = questionnaire.get("otHope", {})
    for niveau in ot_hope.get("niveaux", []):
        for domaine in ot_hope.get("domaines", []):
            code.setdefault(f"{niveau['id']}_{domaine['id']}", []).append("OT Hope (interface4_8.cpp)")

    modele = set()
    for texte in textes_du_modele():
        modele.update(re.findall(r"\{(\w+)\}", texte))
        reste = re.sub(r"\{\w+\}", "", texte)
        if "{" in reste or "}" in reste:
            erreurs.append(f"bilan.docx : accolade isolée ou champ mal écrit dans « {texte.strip()[:80]} ».")
        for ancien in re.findall(r"\bi_[\w/]+", texte):
            erreurs.append(f"bilan.docx : ancien champ {ancien}, à écrire {{…}}.")

    for champ in sorted(modele - code.keys()):
        erreurs.append(f"bilan.docx : le champ {{{champ}}} n'est remplacé nulle part dans le code.")
    for champ, lieux in sorted(code.items()):
        if champ not in modele:
            erreurs.append(f"{', '.join(lieux)} : le champ {{{champ}}} n'existe pas dans bilan.docx.")

    if erreurs:
        print(f"{len(erreurs)} problème(s) entre le contenu et le code :")
        for erreur in erreurs:
            print(f"  - {erreur}")
        return 1
    print(f"Contenu cohérent avec le code : {len(modele)} champs dans bilan.docx, "
          f"{len(chemins)} listes lues dans questionnaire.json.")
    return 0


if __name__ == "__main__":
    sys.stdout.reconfigure(encoding="utf-8")
    sys.exit(main())
