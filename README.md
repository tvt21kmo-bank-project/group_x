# Penkkiprojekti

# kansio api

Kansiossa on sovelluksen REST API

## bank-osan analyysi

### routes/bank.js

const bank = require('../models/bank_model'); <br>
edellisellä lauseella luodaan objekti bank, joka nyt siis viittaa bank_modelista exportattuun objektiin. Jos katsot tiedostoa models/bank_model.js, niin näet, että sen viimeinen rivi exporttaa tuon objektin.

router.post viittaa että tätä endpointia kutsutaan POST metodilla.

bank.debit(request.body, function(err, dbResult) <br>
Viittaa siis bank_modelissa olevaan <b>debit</b> metodiin jolle annetaan parametrina
request.body, joka on siis array, joka sisältää sen mitä http-requestilla lähetetään body-osassa.

 response.json(dbResult.affectedRows); <br>
 Luennolla päädyin siihen että laitetaan http-responsella vastauksena tietokannan
 antama affectedRows arvo, joka on 0, jos transaktio ei onnistunut, eli 
 transaktiossa oleva viimeinen update ei päivittänyt yhtään riviä.

### models/bank_model.js

Täällä on siis määritetty metodit debit ja credit, joita bank.js kutsuu

Ja täällä otetaan se POST-data vastaan arrayna, jolle annoin nimeksi <b>postData</b>.

Nyt on sitten päätetty, että frontendin on lähettävä POST array, jossa kentät: id1, id2, summa