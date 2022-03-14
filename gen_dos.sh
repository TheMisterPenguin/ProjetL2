DIR="obj"
if [ -d "$DIR" ]; then
  echo "Le dossier ${DIR} existe déja !"
else
  echo "Création du dossier ${DIR}"
  mkdir ${DIR}
fi