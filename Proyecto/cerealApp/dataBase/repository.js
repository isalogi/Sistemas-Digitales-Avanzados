var MongoClient = require('mongodb').MongoClient;
var assert = require('assert');

const url = 'mongodb://localhost:27017';
const dbName = 'CerealD';



class Repository {

    constructor() {

    }

    insertAlert(alert, onSucess) {
        const client = new MongoClient(url);

        // Use connect method to connect to the Server
        client.connect(function (err) {
            assert.equal(null, err);

            const db = client.db(dbName);

            const collection = db.collection('alerts');
            // Insert some documents
            collection.insertMany([alert], function (err, result) {

                assert.equal(err, null);
                assert.equal(1, result.result.n);
                assert.equal(1, result.ops.length);

                onSucess(result);
                client.close();

            });
        });

    }

    findAlert(onSucess) {
        const client = new MongoClient(url);

        // Use connect method to connect to the Server
        client.connect(function (err) {
            assert.equal(null, err);

            const db = client.db(dbName);
            const collection = db.collection('alerts');

            collection.find({}).toArray(function (err, docs) {
                assert.equal(err, null);

                onSucess(docs);
                client.close();
            });

        });

    }

}

module.exports = Repository


