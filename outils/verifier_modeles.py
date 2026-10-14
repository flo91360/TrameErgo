"""Vérifie que les modèles Word et le code de TrameErgo utilisent les mêmes champs.

Lancé par la CI (job « build ») et en local : python outils/verifier_modeles.py
Contrôles :
- chaque écran chargé par Word::modele("…") a son modèle pour chaque sexe et âge ;
- chaque champ i_… d'un modèle est remplacé par le code, et inversement ;
- un écran a les mêmes champs dans toutes ses variantes (sexe, âge) ;
- aucun champ n'en contient un autre (Word remplacerait le début du plus long) ;
- l'arborescence ne contient pas de fichier inutilisé.
"""
import re
import sys
import zipfile
from pathlib import Path

RACINE = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(__file__).resolve().parent.parent
ARBO = RACINE / "arborescence"
CHAMP = re.compile(r"i_[\w/]+")
APPEL_CHAMP = re.compile(r'Word::(?:replaceText|replaceTextFromZoneText|insereModele)\(\s*"(i_[^"]+)"')
APPEL_MODELE = re.compile(r'Word::modele\(\s*"([^"]+)"\s*\)')


def sources():
    """Fichiers .cpp compilés, lus dans SOURCES du .pro."""
    pro = (RACINE / "TrameErgo.pro").read_text(encoding="utf-8")
    bloc = re.search(r"SOURCES\s*\+=((?:[^\n]*\\\n)*[^\n]*)", pro).group(1)
    return [RACINE / nom for nom in re.findall(r"[\w./-]+\.cpp", bloc)]


def champs_du_code():
    """{champ: [fichier:ligne, …]} et l'ensemble des écrans chargés par Word::modele."""
    champs, ecrans = {}, set()
    for fichier in sources():
        for numero, ligne in enumerate(fichier.read_text(encoding="utf-8").splitlines(), 1):
            if ligne.lstrip().startswith("//"):
                continue
            for champ in APPEL_CHAMP.findall(ligne):
                champs.setdefault(champ, []).append(f"{fichier.name}:{numero}")
            ecrans.update(APPEL_MODELE.findall(ligne))
    return champs, ecrans


def champs_du_modele(chemin):
    """Champs i_… d'un .docx. Word découpe le texte en morceaux <w:t> : on les
    recolle paragraphe par paragraphe avant de chercher les champs."""
    champs = set()
    with zipfile.ZipFile(chemin) as docx:
        for nom in docx.namelist():
            if not re.fullmatch(r"word/(document|header\d*|footer\d*)\.xml", nom):
                continue
            xml = docx.read(nom).decode("utf-8")
            texte = ""
            for morceau in re.finditer(r"<w:t(?: [^>]*)?>([^<]*)</w:t>|<w:p[ >]|</w:p>|<w:tab/>|<w:br/>", xml):
                if morceau.group(1) is not None:
                    texte += morceau.group(1)
                else:
                    champs.update(CHAMP.findall(texte))
                    texte = ""
            champs.update(CHAMP.findall(texte))
    return champs


def main():
    erreurs = []
    code, ecrans = champs_du_code()
    variantes = sorted(p for p in ARBO.glob("*/*") if p.is_dir())
    if not ecrans:
        erreurs.append("Aucun appel Word::modele(\"…\") trouvé dans le code.")
    if not variantes:
        erreurs.append(f"Aucun dossier <Sexe>/<Âge> dans {ARBO}.")

    attendus = set()
    modeles = {}  # écran -> {variante: champs}
    for variante in variantes:
        for ecran in sorted(ecrans):
            chemin = variante / ecran / f"{ecran}.docx"
            attendus.add(chemin)
            nom = chemin.relative_to(RACINE).as_posix()
            if not chemin.is_file():
                erreurs.append(f"Modèle manquant : {nom}")
                continue
            modeles.setdefault(ecran, {})[variante.relative_to(ARBO).as_posix()] = champs_du_modele(chemin)
            for champ in sorted(modeles[ecran][variante.relative_to(ARBO).as_posix()] - code.keys()):
                erreurs.append(f"{nom} : le champ {champ} n'est remplacé nulle part dans le code.")

    for fichier in sorted(p for p in ARBO.rglob("*") if p.is_file()):
        if fichier not in attendus:
            erreurs.append(f"Fichier inutilisé dans l'arborescence : {fichier.relative_to(RACINE).as_posix()}")

    dans_les_modeles = set().union(*(c for v in modeles.values() for c in v.values()))
    for champ, lieux in sorted(code.items()):
        if champ not in dans_les_modeles:
            erreurs.append(f"{', '.join(lieux)} : le champ {champ} n'existe dans aucun modèle.")

    for ecran, par_variante in sorted(modeles.items()):
        reference = set().union(*par_variante.values())
        for variante, champs in sorted(par_variante.items()):
            for champ in sorted(reference - champs):
                erreurs.append(f"{variante}/{ecran} : le champ {champ} manque (présent dans les autres variantes).")

    tous = sorted(dans_les_modeles | code.keys())
    for court in tous:
        for long in tous:
            if court != long and court in long:
                erreurs.append(f"Le champ {court} est inclus dans {long} : renommer l'un des deux.")

    if erreurs:
        print(f"{len(erreurs)} problème(s) entre les modèles Word et le code :")
        for erreur in erreurs:
            print(f"  - {erreur}")
        return 1
    print(f"Modèles Word cohérents avec le code : {len(variantes)} variantes × {len(ecrans)} écrans, "
          f"{len(code)} champs.")
    return 0


if __name__ == "__main__":
    sys.stdout.reconfigure(encoding="utf-8")
    sys.exit(main())
